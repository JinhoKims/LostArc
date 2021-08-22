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
		ItemTable.Add(ItemClass[i].GetDefaultObject()->ItemName, ItemClass[i]); // 아이템 테이블에 모든 아이템 정보를 넣는다.
	}

	InventorySlot.SetNum(16); // InvenSlot을 Null로 초기화 
}

// Called when the game starts
void ULostArcInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("======================="));
	AddPickupItem("Potion_Health", 17);
	AddPickupItem("Potion_Mana", 8);
	AddPickupItem("Potion_Health", 48);
	AddPickupItem("Potion_Mana", 56);
	UE_LOG(LogTemp, Warning, TEXT("======================="));
	AddPickupItem("Potion_Health", 10);
	AddPickupItem("Potion_Mana", 20);
	AddPickupItem("Potion_Health", 54);
	UE_LOG(LogTemp, Warning, TEXT("======================="));
	AddPickupItem("Potion_Mana", 25);
	AddPickupItem("Potion_Mana", 15);

	UE_LOG(LogTemp, Warning, TEXT("Item Health : %d"), InventorySlot[0]->GetItemQuantity());
	UE_LOG(LogTemp, Warning, TEXT("Item Mana : %d"), InventorySlot[1]->GetItemQuantity());
	
	AddPickupItem("Equip_Ring", 35);
	AddPickupItem("Equip_Ring", 1);
	AddPickupItem("Equip_Ring", 1);

	AddPickupItem("Equip_Earrings", 45);
	AddPickupItem("Equip_Earrings", 50);
	AddPickupItem("Equip_Earrings", 22);
}

void ULostArcInventoryComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	InventorySlot.Empty();
	ItemTable.Empty();
}

// Called every frame
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
			if (!ConsumableItemCheck(NewItem, ItemCount)) // 인벤에 이미 있는지 체크
			{
				for (int i = 0; i < 16; i++)
				{
					if (InventorySlot[i] == nullptr)
					{
						InventorySlot[i] = NewObject<ULostArcItemBase>(this, ItemTable.Find(ItemName)->Get()); // 새로운 아이템을 인벤에 추가
						InventorySlotUpdate.Broadcast(i);
						InventorySlot[i]->AddItemCount(ItemCount); // 수량 증가
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
					InventorySlotUpdate.Broadcast(i);

					ULostArcItemEquipBase* Temp = dynamic_cast<ULostArcItemEquipBase*>(InventorySlot[i]);
					Temp->SetInventoryIndex(i);
					break;
				}
			}
		}
	}
}

void ULostArcInventoryComponent::DeleteItem(int32 Index)
{
	InventorySlot.Remove(InventorySlot[Index]);
}

bool ULostArcInventoryComponent::ConsumableItemCheck(ULostArcItemBase* NewItem, int32 ItemCount)
{
	for (int i = 0; i < 16; i++)
	{
		if (InventorySlot[i] != nullptr)
		{
			if (InventorySlot[i]->ItemName == NewItem->ItemName)
			{
				InventorySlot[i]->AddItemCount(ItemCount); // 수량만 증가
				return true;
			}
		}
	}
	return false;
}

ULostArcItemBase* ULostArcInventoryComponent::GetSlotItem(int32 Index)
{
	if (InventorySlot[Index] == nullptr)
		return nullptr;
	else
		return InventorySlot[Index];
}

void ULostArcInventoryComponent::InventorySlotChangeNullptr(int32 Index)
{
	InventorySlot[Index] = nullptr;
	InventorySlotUpdate.Broadcast(Index);
}
