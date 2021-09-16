// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Quick/LostArcUIQuick.h"
#include "UI/Quick/LostArcUIQuickSlot.h"
#include "Component/LostArcCharacterAbilityComponent.h"
#include "Component/LostArcInventoryComponent.h"

void ULostArcUIQuick::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 16; i++)
	{
		QuickSlot.Add(Cast<ULostArcUIQuickSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_QuickSlot_%d"), i)))));
		QuickSlot[i]->SetSlotIndex(i);

		auto OwingChar = Cast<ALostArcCharacter>(GetOwningPlayerPawn());
		if(i < 8)
		{
			QuickSlot[i]->SetSlotComponent(OwingChar->AbilityComponent);
			QuickSlot[i]->SetQuickSlotType(EQuickSlotType::Ability);
		}
		else
		{
			QuickSlot[i]->SetSlotComponent(OwingChar->InventoryComponent);
			QuickSlot[i]->SetQuickSlotType(EQuickSlotType::Potion);
		}
	}
}
