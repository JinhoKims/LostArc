// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LostArcUIInventory.h"
#include "UI/Inventory/LostArcUIInventorySlot.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcInventoryComponent.h"


void ULostArcUIInventory::NativeConstruct()
{
	for (int i = 0; i < 16; i++)
	{
		InventorySlot.Add(Cast<ULostArcUIInventorySlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BPInventory_Slot_%d"), i)))));
	}

	auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());
//	Character->InventoryComponent->InventorySlotUpdate.AddUObject(this, &ULostArcUIInventory::InventorySlotConstruct);
//	Character->InventoryComponent->InventorySlotEmpty.AddUObject(this, &ULostArcUIInventory::InventorySlotClear);
}

void ULostArcUIInventory::BeginDestroy()
{
	Super::BeginDestroy();
	InventorySlot.Empty();
}

void ULostArcUIInventory::InventorySlotConstruct(int32 SlotIndex)
{
	auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

//	InventorySlot[SlotIndex]->Item = Character->InventoryComponent->GetSlotItem(SlotIndex);

	if (InventorySlot[SlotIndex]->Item != nullptr)
	{
		InventorySlot[SlotIndex]->BindItemDelegate();
	}
}

void ULostArcUIInventory::UpdateItemQuantity(int32 SlotIndex)
{
	if (InventorySlot[SlotIndex]->Item != nullptr)
	{
		InventorySlot[SlotIndex]->UpdateItemQuantity();
	}
}

void ULostArcUIInventory::InventorySlotClear(int32 SlotIndex)
{
	InventorySlot[SlotIndex]->ClearItemDelegate();
}
