// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LostArcUIInven.h"
#include "UI/Inventory/LostArcUIInvenSlot.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcInventoryComponent.h"

void ULostArcUIInven::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerCharacter = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	for (int i = 0; i < 16; i++)
	{
		InvenSlot.Add(Cast<ULostArcUIInvenSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BPInven_Slot_%d"), i)))));
		InvenSlot[i]->SetSlotIndex(i);
	}
}

void ULostArcUIInven::BeginDestroy()
{
	Super::BeginDestroy();
	InvenSlot.Empty();
}

void ULostArcUIInven::ConstructSlot(int32 Index)
{
	InvenSlot[Index]->SetSlotData(OwnerCharacter->InventoryComponent->GetItemData(Index));
}