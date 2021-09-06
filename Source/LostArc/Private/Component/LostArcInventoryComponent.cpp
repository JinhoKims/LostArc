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

ULostArcAbilityBase* ULostArcInventoryComponent::TransAbil(int32 SlotIndex)
{
	auto TransUnit = GetSlotData(SlotIndex);

	if(TransUnit != nullptr)
	{
		InventorySlot[SlotIndex] = nullptr;
		InvenSlotUpdate.Broadcast(SlotIndex);
		return TransUnit;
	}
	
	return nullptr;
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

void ULostArcInventoryComponent::SwappingSlot(UActorComponent* OwnerComponent, int32 OwnerIndex, int32 DistIndex)
{
	// 인벤에 장비아이템 삽입
	ILostArcCharacterInterface * Inter = Cast<ILostArcCharacterInterface>(OwnerComponent); // 나중에 수정하기!!
	
	auto EquipComponent = Cast<ULostArcCharacterEquipComponent>(OwnerComponent);
	if(EquipComponent == nullptr || EquipComponent->GetEquipItem(OwnerIndex) == nullptr) return;
	
	if(InventorySlot[DistIndex] == nullptr) // Drop 위치의 슬롯이 null일 때
	{
		SetSlotData(Cast<ULostArcItemEquipBase>(EquipComponent->TransAbil(OwnerIndex)), DistIndex);
	}
	else if (Cast<ULostArcItemEquipBase>(InventorySlot[DistIndex]) != nullptr)// Drop 위치의 슬롯이 유효하며, EquipSlot일 때
	{
		if(Cast<ULostArcItemEquipBase>(InventorySlot[DistIndex])->GetAcType() == EquipComponent->GetEquipItem(OwnerIndex)->GetAcType())
		{
			EquipComponent->SwappingSlot(this, DistIndex, OwnerIndex);
		}
	}
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

bool ULostArcInventoryComponent::SetSlotData(ULostArcItemBase* OwnerItem)
{
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

bool ULostArcInventoryComponent::SetSlotData(ULostArcItemBase* OwnerItem, int32 DistIndex)
{
	if(InventorySlot[DistIndex] == nullptr)
	{
		InventorySlot[DistIndex] = OwnerItem;
		InvenSlotUpdate.Broadcast(DistIndex);
		return true;
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