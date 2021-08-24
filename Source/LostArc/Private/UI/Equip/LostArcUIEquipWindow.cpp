// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Equip/LostArcUIEquipWindow.h"
#include "UI/Equip/LostArcUIEquipSlot.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcCharacterEquipComponent.h"

void ULostArcUIEquipWindow::NativeConstruct()
{
	Super::NativeConstruct();
	auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	Equip_NecklaceSlot.Add(Cast<ULostArcUIEquipSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_Equip_Slot_Necklace"))))));

	for (int i = 0; i < 2; i++)
	{
		Equip_EarringSlot.Add(Cast<ULostArcUIEquipSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BPEquip_Slot_Earring_%d"), i)))));
	}

	for (int i = 0; i < 2; i++)
	{
		Equip_RingSlot.Add(Cast<ULostArcUIEquipSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BPEquip_Slot_Ring_%d"), i)))));
	}

	Character->EquipComponent->EquipSlotUpdate.AddUObject(this, &ULostArcUIEquipWindow::EquipSlotConstruct);
	Character->EquipComponent->EquipSlotClear.AddUObject(this, &ULostArcUIEquipWindow::EquipSlotClear);
}

void ULostArcUIEquipWindow::BeginDestroy()
{
	Super::BeginDestroy();

	Equip_NecklaceSlot.Empty();
	Equip_EarringSlot.Empty();
	Equip_RingSlot.Empty();
}

void ULostArcUIEquipWindow::EquipSlotConstruct(EAccessoryType Type, int32 SlotIndex)
{
	auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	switch (Type)
	{
	case Necklace:
		Equip_NecklaceSlot[SlotIndex]->EquipItem = Character->EquipComponent->GetEquipItem(Type, SlotIndex);
		if (Equip_NecklaceSlot[SlotIndex]->EquipItem != nullptr)
		{
			Equip_NecklaceSlot[SlotIndex]->BindEquipDelegate();
		}
		break;
	case Earring:
		Equip_EarringSlot[SlotIndex]->EquipItem = Character->EquipComponent->GetEquipItem(Type, SlotIndex);
		if (Equip_EarringSlot[SlotIndex]->EquipItem != nullptr)
		{
			Equip_EarringSlot[SlotIndex]->BindEquipDelegate();
		}
		break;
	case Ring:
		Equip_RingSlot[SlotIndex]->EquipItem = Character->EquipComponent->GetEquipItem(Type, SlotIndex);
		if (Equip_RingSlot[SlotIndex]->EquipItem != nullptr)
		{
			Equip_RingSlot[SlotIndex]->BindEquipDelegate();
		}
		break;
	}
}

void ULostArcUIEquipWindow::EquipSlotClear(EAccessoryType Type, int32 SlotIndex)
{
	auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	switch (Type)
	{
	case Necklace:
		Equip_NecklaceSlot[SlotIndex]->ClearEquipDelegate();
		break;
	case Earring:
		Equip_EarringSlot[SlotIndex]->ClearEquipDelegate();
		break;
	case Ring:
		Equip_RingSlot[SlotIndex]->ClearEquipDelegate();
		break;
	}
}
