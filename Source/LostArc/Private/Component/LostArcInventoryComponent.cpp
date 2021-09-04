// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcInventoryComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "Component/LostArcCharacterEquipComponent.h"
#include "UI/LostArcUIMainHUD.h"
#include "UI/Inventory/LostArcUIInventory.h"
#include "UI/Inventory/LostArcUIInventorySlot.h"
#include "Controller/LostArcPlayerController.h"

// Sets default values for this component's properties
ULostArcInventoryComponent::ULostArcInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	ItemClass.Init(ULostArcItemBase::StaticClass(), 5);
}

void ULostArcInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (int i = 0; i < 5; i++)
	{
		ItemTable.Add(ItemClass[i].GetDefaultObject()->GetName(), ItemClass[i]); // 아이템 테이블에 모든 아이템 정보를 넣는다.
	}
	InventorySlot.SetNum(16); // InvenSlot을 Null로 초기화 
}

// Called when the game starts
void ULostArcInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AddPickupItem("Potion_Health", 3);
	AddPickupItem("Potion_Mana", 3);

	UE_LOG(LogTemp, Warning, TEXT("Item Health : %d"), InventorySlot[0]->GetItemQuantity());
	UE_LOG(LogTemp, Warning, TEXT("Item Mana : %d"), InventorySlot[1]->GetItemQuantity());
	
	//AddPickupItem("Equip_Ring");
	//AddPickupItem("Equip_Ring");
	//AddPickupItem("Equip_Ring");

	//AddPickupItem("Equip_Earrings");
	//AddPickupItem("Equip_Earrings");
	//AddPickupItem("Equip_Earrings");
}

void ULostArcInventoryComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	InventorySlot.Empty();
	ItemTable.Empty();
}

void ULostArcInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULostArcInventoryComponent::AddPickupItem(FString ItemName, int32 ItemCount)
{
	if (ItemTable.Find(ItemName) == nullptr) return;
	auto NewItem = ItemTable.Find(ItemName)->GetDefaultObject();

	if (NewItem)
	{
		if (NewItem->IsConsumable()) // 소비 아이템
		{
			if (!ConsumableCheck(NewItem, ItemCount)) // 인벤에 이미 있는지 체크
			{
				for (int i = 0; i < 16; i++)
				{
					if (InventorySlot[i] == nullptr)
					{
						InventorySlot[i] = NewObject<ULostArcItemBase>(this, ItemTable.Find(ItemName)->Get()); // 새로운 아이템을 인벤에 추가
						InventorySlot[i]->SetItemQuantity(ItemCount); // 수량 증가
						InvenSlotUpdate.Broadcast(i);
						break;
					}
				}
			}
		}
		else // 장비 아이템
		{
			for (int i = 0; i < 16; i++)
			{
				if (InventorySlot[i] == nullptr)
				{
					InventorySlot[i] = NewObject<ULostArcItemBase>(this, ItemTable.Find(ItemName)->Get());
					InvenSlotUpdate.Broadcast(i);
					break;
				}
			}
		}
	}
}

void ULostArcInventoryComponent::UseItem(int32 SlotIndex)
{
	if (InventorySlot[SlotIndex] != nullptr)
	{
		if (InventorySlot[SlotIndex]->Use(Cast<ALostArcCharacter>(GetOwner()))) // 아이템을 모두 소모했을 경우
		{
			InventorySlot[SlotIndex] = nullptr;
			InvenSlotUpdate.Broadcast(SlotIndex);
		}
	}
}

void ULostArcInventoryComponent::SwapSlot(int32 ownerIndex, int32 distIndex)
{
	if (InventorySlot[ownerIndex] == nullptr) return;

	if (InventorySlot[distIndex] == nullptr)
	{
		InventorySlot[distIndex] = InventorySlot[ownerIndex];
		InventorySlot[ownerIndex] = nullptr;
	}
	else
	{
		if (!GetOwner()->GetWorldTimerManager().IsTimerActive(InventorySlot[distIndex]->AbilityCDProperty.Key))
		{
			if (InventorySlot[ownerIndex]->GetName().Equals(InventorySlot[distIndex]->GetName()))
			{
				InventorySlot[distIndex]->SetItemQuantity(InventorySlot[ownerIndex]->GetItemQuantity());
			}
			else
			{
				Swap(InventorySlot[ownerIndex], InventorySlot[distIndex]);
			}
		}
	}

	InvenSlotUpdate.Broadcast(ownerIndex);
	InvenSlotUpdate.Broadcast(distIndex);
}

void ULostArcInventoryComponent::MoveItem(ULostArcItemBase* OwnerItem, int32 distIndex)
{
	switch (OwnerItem->GetItemType())
	{
	case ITEM_Equip:
		if (distIndex >= 0) // 아이템 슬롯과 장비 슬롯을 스왑
		{
			if (InventorySlot[distIndex] == nullptr)
			{
				InventorySlot[distIndex] = OwnerItem;
				InvenSlotUpdate.Broadcast(distIndex);
			}
			else // =! nullptr
			{
				if (InventorySlot[distIndex]->GetItemType() == ITEM_Equip)
				{
					if (dynamic_cast<ULostArcItemEquipBase*>(OwnerItem)->GetType() == dynamic_cast<ULostArcItemEquipBase*>(InventorySlot[distIndex])->GetType())
					{
						Swap(OwnerItem, InventorySlot[distIndex]);
						InvenSlotUpdate.Broadcast(distIndex);
						(Cast<ALostArcCharacter>(GetOwner()))->EquipComponent->EquipMounts(dynamic_cast<ULostArcItemEquipBase*>(OwnerItem));
					}
				}
			}
		}
		else 
		{
			for (int i = 0; i < 16; i++)
			{
				if (InventorySlot[i] == nullptr)
				{
					InventorySlot[i] = OwnerItem;
					InvenSlotUpdate.Broadcast(i);
					break;
				}
			}
		}
		break;
	case ITEM_Potion:
		// SwapSlot
		break;
	case ITEM_None:
		break;
	}
}

bool ULostArcInventoryComponent::ConsumableCheck(ULostArcItemBase* NewItem, int32 ItemCount)
{
	for (int i = 0; i < 16; i++)
	{
		if (InventorySlot[i] != nullptr)
		{
			if (InventorySlot[i]->GetName() == NewItem->GetName()) // 인벤에 이미 있으면
			{
				InventorySlot[i]->SetItemQuantity(ItemCount); // 수량만 증가
				return true;
			}
		}
	}
	return false;
}

ULostArcAbilityBase* ULostArcInventoryComponent::GetSlotData(int32 Index)
{
	if (InventorySlot[Index] == nullptr)
		return nullptr;
	else
		return dynamic_cast<ULostArcAbilityBase*>(InventorySlot[Index]);
}