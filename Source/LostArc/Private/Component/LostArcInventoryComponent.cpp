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
		// 여러번 클릭시 자주 튕기니 글로벌(아이템에도) 쿨타임 필요 
		if (InventorySlot[SlotIndex]->Use(Cast<ALostArcCharacter>(GetOwner()))) // 아이템을 모두 소모했을 경우
		{
			InventorySlot[SlotIndex] = nullptr;
			InvenSlotUpdate.Broadcast(SlotIndex);
		}
	}
}
void ULostArcInventoryComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent)
{
	if(OwnerComponent == nullptr)
	{
		if(GetAbility(OwnerIndex) == nullptr || OwnerIndex == DistIndex) return;

		if (GetAbility(DistIndex) == nullptr)
		{
			SetAbility(GetAbility(OwnerIndex,true), DistIndex);
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
				InvenSlotUpdate.Broadcast(OwnerIndex);
				InvenSlotUpdate.Broadcast(DistIndex);
			}
		}
	}
	else
	{
		ILostArcCharacterInterface* Interface = Cast<ILostArcCharacterInterface>(OwnerComponent);
		if(Interface == nullptr) return;
		
		auto OwnerItem = Cast<ULostArcItemBase>(Interface->GetAbility(OwnerIndex));
		if(OwnerItem == nullptr) return;
		
		if(GetAbility(DistIndex) == nullptr) // Drop 위치의 슬롯이 null일 때
		{
			SetAbility(Interface->GetAbility(OwnerIndex,true), DistIndex);
		}
		else if(Cast<ULostArcItemEquipBase>(InventorySlot[DistIndex]) != nullptr) // null이 아닐 떄
		{ // Owner와 this가 소비형 아이템(IsConsumable)일 경우 어빌리티 이름(Name)을 체크하여 같으면 수량 증가
			// 둘 다 소비형 아이템이 아닐 경우 Interface->SetAbility()를 호출하여 스왑 시도
			// 둘 중 하나만 소비형일 경우 거래 자체가 불가능하니 슬롯상태 현상유지(리턴)
			if(Cast<ULostArcItemEquipBase>(InventorySlot[DistIndex])->GetAcType() == Cast<ULostArcItemEquipBase>(Interface->GetAbility(OwnerIndex))->GetAcType())
			{
				Interface->SwappingSlot(DistIndex, OwnerIndex, this);
			}
		}
	}
	
}
ULostArcAbilityBase* ULostArcInventoryComponent::GetAbility(int32 SlotIndex, bool bTrans)
{
	if(bTrans)
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
	else
	{
		if (InventorySlot[SlotIndex] == nullptr)
			return nullptr;
		else
			return InventorySlot[SlotIndex];
	}
}
bool ULostArcInventoryComponent::SetAbility(ULostArcAbilityBase* OwnerAbility, int32 SlotIndex)
{
	auto OwnerItem = Cast<ULostArcItemBase>(OwnerAbility);
	if(OwnerItem == nullptr) return false;
	
	if(SlotIndex == -1)
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
	else
	{
		if(InventorySlot[SlotIndex] == nullptr)
		{
			InventorySlot[SlotIndex] = OwnerItem;
			InvenSlotUpdate.Broadcast(SlotIndex);
			return true;
		}
		
		return false;
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