// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIInventory.h"
#include "UI/LostArcUIInventorySlot.h"

void ULostArcUIInventory::NativeConstruct()
{
	for (int i = 0; i < 16; i++)
	{
		InventorySlots.Add(Cast<ULostArcUIInventorySlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BPInventory_Slot_%d"), i)))));
	}
}