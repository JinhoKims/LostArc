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

void ULostArcCharacterEquipComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	EquipSlot.Empty();
}

void ULostArcCharacterEquipComponent::UseAbility(int32 SlotIndex)
{
	const EAccessoryType SlotType = IndexDecoding(SlotIndex);
	
	if(EquipSlot.Find(SlotType)->EquipArray[SlotIndex] != nullptr)
	{
		if(Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->ReceiveSlot(EquipSlot.Find(SlotType)->EquipArray[SlotIndex]))
		{
			EquipSlot.Find(SlotType)->EquipArray[SlotIndex]->Dismount(Cast<ALostArcCharacter>(GetOwner()));
			EquipSlot.Find(SlotType)->EquipArray[SlotIndex] = nullptr;
			EquipSlotUpdate.Broadcast(IndexEncoding(SlotType, SlotIndex));
		}
	}
}

void ULostArcCharacterEquipComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex)
{
	auto OwnerType = IndexDecoding(OwnerIndex);
	auto DistType = IndexDecoding(DistIndex);
	
	if(EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex] == nullptr || OwnerIndex == DistIndex || OwnerType != DistType ) return;
	
	if (EquipSlot.Find(DistType)->EquipArray[DistIndex] == nullptr)
	{
		EquipSlot.Find(DistType)->EquipArray[DistIndex] = EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex];
		EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex] = nullptr;
		UE_LOG(LogTemp,Warning,TEXT("Move Slot"));
	}
	else
	{
		Swap(EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex],
			EquipSlot.Find(DistType)->EquipArray[DistIndex]);
		UE_LOG(LogTemp,Warning,TEXT("Swap Slot"));
	}

	EquipSlotUpdate.Broadcast(IndexEncoding(OwnerType,OwnerIndex));
	EquipSlotUpdate.Broadcast(IndexEncoding(DistType,DistIndex));
}

void ULostArcCharacterEquipComponent::EquipMounts(ULostArcItemEquipBase* NewEquip)
{
	if (NewEquip == nullptr) return;
	
	for (int32 i = 0; i < *EquipMaxSlot.Find(NewEquip->GetAcType()); i++) // EquipSlot has Empty
	{
		if(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i]==nullptr)
		{
			EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i] = NewEquip;
			EquipSlotUpdate.Broadcast(IndexEncoding(NewEquip->GetAcType(), i));
			return;
		}
	}
	// EquipSlot has Fully
	Swap(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[0], NewEquip);
	EquipSlotUpdate.Broadcast(IndexEncoding(NewEquip->GetAcType(), 0));
	NewEquip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
	Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->ReceiveSlot(NewEquip);
}

EAccessoryType ULostArcCharacterEquipComponent::IndexDecoding(int32& SlotIndex)
{
	switch (SlotIndex)
	{
	case 0:
		return EAccessoryType::Necklace;
	case 1:
	case 2:
		SlotIndex-=1;
		return EAccessoryType::Earring;
	case 3:
	case 4:
		SlotIndex-=3;
		return EAccessoryType::Ring;
	}
	
	return EAccessoryType::Necklace;
}

int32 ULostArcCharacterEquipComponent::IndexEncoding(EAccessoryType AcType, int32 Index)
{
	switch (AcType)
	{
	case EAccessoryType::Necklace:
		return Index;
	case EAccessoryType::Earring:
		return Index+=1;
	case EAccessoryType::Ring:
		return Index+=3;
	}
	
	return -1;
}

ULostArcItemEquipBase* ULostArcCharacterEquipComponent::GetEquipItem(int32 Index)
{
	return EquipSlot.Find(IndexDecoding(Index))->EquipArray[Index];
}
