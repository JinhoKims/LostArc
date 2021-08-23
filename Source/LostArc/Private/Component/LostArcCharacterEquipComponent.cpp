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

ULostArcItemBase* ULostArcCharacterEquipComponent::EquipmentMounts(ULostArcItemEquipBase* NewEquip, EAccessoryType Type)
{
	if (NewEquip == nullptr) return nullptr;

	switch (Type)
	{
	case Necklace:
		break;
	case Earring:
		for (int i = 0; i < 2; i++)
		{
			if (EarringSlot[i] == nullptr)
			{
				EarringSlot[i] = NewEquip;
				EquipSlotUpdate.Broadcast(Type, i);
				return nullptr;
			}
		} // slot saturation
		// Broadcast
		return NewEquip;
		break;
	case Ring:
		for (int i = 0; i < 2; i++)
		{
			if (RingSlot[i] == nullptr)
			{
				RingSlot[i] = NewEquip;
				EquipSlotUpdate.Broadcast(Type, i);
				return nullptr;
			}
		} // slot saturation
		// Broadcast
		return NewEquip;
		break;
	}

	return nullptr;
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
