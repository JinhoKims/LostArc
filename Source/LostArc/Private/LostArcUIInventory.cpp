// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcUIInventory.h"
#include "LostArcUIInventorySlot.h"

void ULostArcUIInventory::NativeConstruct()
{
	for (int i = 0; i < 32; i++)
	{
		InventorySlots.Add(Cast<ULostArcUIInventorySlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BPInventory_Slot_%d"), i)))));
	}
}