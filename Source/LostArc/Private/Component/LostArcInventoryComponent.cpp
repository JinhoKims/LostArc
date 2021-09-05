// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcInventoryComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "Component/LostArcCharacterEquipComponent.h"
#include "UI/Inventory/LostArcUIInventory.h"

ULostArcInventoryComponent::ULostArcInventoryComponent()
{
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

void ULostArcInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AddPickupItem("Potion_Health", 3);
	AddPickupItem("Potion_Mana", 3);

	AddPickupItem("Potion_Health", 8);
	AddPickupItem("Potion_Mana", 7);
	
	AddPickupItem("Equip_Ring");
	AddPickupItem("Equip_Ring");
	AddPickupItem("Equip_Ring");

	AddPickupItem("Equip_Earrings");
	AddPickupItem("Equip_Earrings");
	AddPickupItem("Equip_Earrings");
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

void ULostArcInventoryComponent::UseAbility(int32 SlotIndex)
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

bool ULostArcInventoryComponent::ReceiveItem(ULostArcItemBase* OwnerItem)
{
	if(OwnerItem == nullptr) return false;
	
	for(int i = 0; i < 16; i++)
	{
		if(InventorySlot[i] == nullptr)
		{
			InventorySlot[i] = OwnerItem;
			InvenSlotUpdate.Broadcast(i);
			return true;
		}
	}		
	
	return false;
}

bool ULostArcInventoryComponent::ReceiveItem(ULostArcItemBase* OwnerItem, int32 OwerIndex, int32 DistIndex)
{
	if(OwnerItem == nullptr) return false;

	if(InventorySlot[DistIndex] == nullptr)
	{
		InventorySlot[DistIndex] = OwnerItem;
		InvenSlotUpdate.Broadcast(DistIndex);
		return true;
	}
	else
	{
		if(OwnerItem->GetItemType() == InventorySlot[DistIndex]->GetItemType())
		{
			Cast<ALostArcCharacter>(GetOwner())->EquipComponent->ReceiveSlot(DistIndex, OwerIndex);
			return false;
		}
	}

	return false;
}

void ULostArcInventoryComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex)
{
	if (InventorySlot[OwnerIndex] == nullptr || OwnerIndex == DistIndex) return;

	if (InventorySlot[DistIndex] == nullptr)
	{
		InventorySlot[DistIndex] = InventorySlot[OwnerIndex];
		InventorySlot[OwnerIndex] = nullptr;
	}
	else
	{
		if (!GetOwner()->GetWorldTimerManager().IsTimerActive(InventorySlot[DistIndex]->AbilityCDProperty.Key))
		{
			if (InventorySlot[OwnerIndex]->GetName().Equals(InventorySlot[DistIndex]->GetName())) // 같은 아이템이 있고
			{
				if (EItemType::ITEM_Equip != InventorySlot[OwnerIndex]->GetItemType()) // 장비 아이템이 아닌경우
				{
					InventorySlot[DistIndex]->SetItemQuantity(InventorySlot[OwnerIndex]->GetItemQuantity()); // 합체
					InventorySlot[OwnerIndex] = nullptr;
				}
			}
			else
			{
				Swap(InventorySlot[OwnerIndex], InventorySlot[DistIndex]);
			}
		}
	}

	InvenSlotUpdate.Broadcast(OwnerIndex);
	InvenSlotUpdate.Broadcast(DistIndex);
}

bool ULostArcInventoryComponent::ReceiveSlot(int32 OwnerIndex, int32 DistIndex)
{
	return Cast<ALostArcCharacter>(GetOwner())->EquipComponent->SendSlot(OwnerIndex, DistIndex);
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
					if (dynamic_cast<ULostArcItemEquipBase*>(OwnerItem)->GetAcType() == dynamic_cast<ULostArcItemEquipBase*>(InventorySlot[distIndex])->GetAcType())
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

ULostArcItemBase* ULostArcInventoryComponent::GetSlotData(int32 Index)
{
	if (InventorySlot[Index] == nullptr)
		return nullptr;
	else
		return InventorySlot[Index];
}