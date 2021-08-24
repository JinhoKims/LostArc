// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"


// Sets default values for this component's properties
ULostArcCharacterEquipComponent::ULostArcCharacterEquipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void ULostArcCharacterEquipComponent::InitializeComponent()
{
	Super::InitializeComponent();
	NecklaceSlot.SetNum(1);
	EarringSlot.SetNum(2);
	RingSlot.SetNum(2);
}

// Called when the game starts
void ULostArcCharacterEquipComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ULostArcCharacterEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool ULostArcCharacterEquipComponent::EquipmentMounts(ULostArcItemEquipBase* NewEquip, EAccessoryType Type)
{
	if (NewEquip == nullptr) return false;

	switch (Type)
	{
	case Necklace:
		for (int i = 0; i < 1; i++)
		{
			if (NecklaceSlot[i] == nullptr)
			{
				NecklaceSlot[i] = NewEquip;
				NecklaceSlot[i]->SetEquipSlotIndex(i);
				EquipSlotUpdate.Broadcast(Type, i);
				return true;
			}
		}
		break;
	case Earring:
		for (int i = 0; i < 2; i++)
		{
			if (EarringSlot[i] == nullptr)
			{
				EarringSlot[i] = NewEquip;
				EarringSlot[i]->SetEquipSlotIndex(i);
				EquipSlotUpdate.Broadcast(Type, i);
				return true;
			}
		} // slot saturation
		// Broadcast
		break;
	case Ring:
		for (int i = 0; i < 2; i++)
		{
			if (RingSlot[i] == nullptr)
			{
				RingSlot[i] = NewEquip;
				RingSlot[i]->SetEquipSlotIndex(i);
				EquipSlotUpdate.Broadcast(Type, i);
				return true;
			}
		} // slot saturation
		// Broadcast
		break;
	}
	return false;
}

ULostArcItemEquipBase* ULostArcCharacterEquipComponent::GetEquipItem(EAccessoryType Type, int32 Index)
{
	switch (Type)
	{
	case Necklace:
		return NecklaceSlot[Index];
	case Earring:
		return EarringSlot[Index];
	case Ring:
		return RingSlot[Index];
	}

	return nullptr;
}

void ULostArcCharacterEquipComponent::DismountEquip(EAccessoryType Type, int32 Index)
{
	auto Char = Cast<ALostArcCharacter>(GetOwner());
	ULostArcItemBase* OwingItem;

	switch (Type)
	{
	case Necklace:
		OwingItem = dynamic_cast<ULostArcItemBase*>(NecklaceSlot[Index]);
		if (OwingItem != nullptr)
		{
			EquipSlotClear.Broadcast(Type,Index);
			NecklaceSlot[Index] = nullptr;
			Char->InventoryComponent->MoveItem(OwingItem);
		}
		break;
	case Earring:
		OwingItem = dynamic_cast<ULostArcItemBase*>(EarringSlot[Index]);
		if (OwingItem != nullptr)
		{
			EquipSlotClear.Broadcast(Type, Index);
			EarringSlot[Index] = nullptr;
			Char->InventoryComponent->MoveItem(OwingItem);
		}
		break;
	case Ring:
		OwingItem = dynamic_cast<ULostArcItemBase*>(RingSlot[Index]);
		if (OwingItem != nullptr)
		{
			EquipSlotClear.Broadcast(Type, Index);
			RingSlot[Index] = nullptr;
			Char->InventoryComponent->MoveItem(OwingItem);
		}
		break;
	}
}
