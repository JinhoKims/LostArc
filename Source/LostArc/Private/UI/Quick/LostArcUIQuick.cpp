// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Quick/LostArcUIQuick.h"
#include "Abilities/Skill/LostArcSkillBase.h"
#include "Component/LostArcCharacterAbilityComponent.h"
#include "UI/Quick/LostArcUIQuickSlot.h"
#include "Component/LostArcQuickSlotComponent.h"

void ULostArcUIQuick::ClearQuickSlot(int32 SlotIndex)
{
	QuickSlot[SlotIndex]->ClearSlotData();
}

void ULostArcUIQuick::NativeConstruct()
{
	Super::NativeConstruct();
	auto OwingChar = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	for (int i = 0; i < 16; i++)
	{
		QuickSlot.Add(Cast<ULostArcUIQuickSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_QuickSlot_%d"), i)))));
		QuickSlot[i]->SetSlotComponent(OwingChar->QuickSlotComponent);
		QuickSlot[i]->SetSlotIndex(i);
		
		if(i < 8)
		{
			QuickSlot[i]->SetQuickSlotType(EQuickSlotType::Ability);
			QuickSlot[i]->SetSlotDataFromAbilityCompo(OwingChar->AbilityComponent->GetAbilites(static_cast<EAbilityType>(i+1)));
			OwingChar->AbilityComponent->GetAbilites(static_cast<EAbilityType>(i+1))->AbilityCDProperty.Value.AddUObject(QuickSlot[i], &ULostArcUIQuickSlot::SetNativeTick);
		}
		else
		{
			QuickSlot[i]->SetQuickSlotType(EQuickSlotType::Potion);
		}
	}
	
	BP_EvadeSlot->SetEvadeSlot(OwingChar->AbilityComponent->GetAbilites(EAbilityType::Evade));
	OwingChar->AbilityComponent->GetAbilites(EAbilityType::Evade)->AbilityCDProperty.Value.AddUObject(BP_EvadeSlot, &ULostArcUISlotBase::SetNativeTick);
}
