// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Quick/LostArcUIQuick.h"
#include "UI/Quick/LostArcUIQuickSlot.h"
#include "Component/LostArcQuickSlotComponent.h"
#include "Component/LostArcInventoryComponent.h"

void ULostArcUIQuick::ClearQuickSlot(int32 SlotIndex)
{
	QuickSlot[SlotIndex]->ClearSlotData();
}

void ULostArcUIQuick::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 16; i++)
	{
		auto OwingChar = Cast<ALostArcCharacter>(GetOwningPlayerPawn());
		
		QuickSlot.Add(Cast<ULostArcUIQuickSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_QuickSlot_%d"), i)))));
		QuickSlot[i]->SetSlotComponent(OwingChar->QuickSlotComponent);
		QuickSlot[i]->SetSlotIndex(i);
		
		if(i < 8)
		{
			QuickSlot[i]->SetQuickSlotType(EQuickSlotType::Ability);
			QuickSlot[i]->SetIcon(true);
		}
		else
		{
			QuickSlot[i]->SetQuickSlotType(EQuickSlotType::Potion);
		}
	}
}
