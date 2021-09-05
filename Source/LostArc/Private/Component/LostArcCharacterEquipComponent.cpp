// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "Abilities/Items/Equip/LostArcItemEquip_Earrings.h"

// Sets default values for this component's properties
ULostArcCharacterEquipComponent::ULostArcCharacterEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	for (int i = 0; i < 3; i++)
	{
		EquipSlot.Add((EAccessoryType)i);
		EquipMaxSlot.Add((EAccessoryType)i);
	}
}

void ULostArcCharacterEquipComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	for (int32 i = 0; i < 3; i++)
	{
		if (EquipMaxSlot.Find((EAccessoryType)i) != nullptr)
		{
			EquipSlot.Find((EAccessoryType)i)->EquipArray.SetNum(*EquipMaxSlot.Find((EAccessoryType)i));
		}
	}
}

void ULostArcCharacterEquipComponent::UseAbility(int32 SlotIndex)
{
	EAccessoryType TempType;
	switch (SlotIndex)
	{
	case 0:
		TempType = EAccessoryType::Necklace;
		break;
	case 1:
	case 2:
		TempType = EAccessoryType::Earring;
		SlotIndex-=1;
		break;
	case 3:
	case 4:
		TempType = EAccessoryType::Ring;
		SlotIndex-=3;
		break;
	}
	
	if(EquipSlot.Find(TempType)->EquipArray[SlotIndex] != nullptr)
	{
		Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->MoveItem(EquipSlot.Find(TempType)->EquipArray[SlotIndex]);
		EquipSlot.Find(TempType)->EquipArray[SlotIndex] = nullptr;
		EquipSlotUpdate.Broadcast(TempType, SlotIndex);
	}
}

void ULostArcCharacterEquipComponent::EquipMounts(ULostArcItemEquipBase* NewEquip)
{
	if (NewEquip == nullptr) return;
	
	for (int32 i = 0; i < *EquipMaxSlot.Find(NewEquip->GetAcType()); i++) // EquipSlot has Empty
	{
		if(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i]==nullptr)
		{
			EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i] = NewEquip;
			EquipSlotUpdate.Broadcast(NewEquip->GetAcType(), i);
			return;
		}
	}
	
	// EquipSlot has Fully
	Swap(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[0], NewEquip);
	EquipSlotUpdate.Broadcast(NewEquip->GetAcType(), 0);
	Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->MoveItem(NewEquip);
}

ULostArcItemEquipBase* ULostArcCharacterEquipComponent::GetEquipItem(EAccessoryType Type, int32 SlotIndex)
{
	return EquipSlot.Find(Type)->EquipArray[SlotIndex];
}