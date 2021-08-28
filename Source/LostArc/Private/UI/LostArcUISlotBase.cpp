// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LostArcUISlotBase.h"
#include "Character/LostArcCharacter.h"
#include "Abilities/LostArcAbilityBase.h"


void ULostArcUISlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	bEnableTick = false;
	SlotIndex = 0;
}

void ULostArcUISlotBase::SetNativeTick(bool CD)
{
	bEnableTick = CD;
}

void ULostArcUISlotBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bEnableTick) 
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
		auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

		float Value = GetOwningPlayer()->GetWorldTimerManager().GetTimerRemaining(SlotData->AbilityCDProperty.Key) / SlotData->GetCDTime();
		Image_CD->GetDynamicMaterial()->SetScalarParameterValue(FName(TEXT("Progress")), Value < 0.002f ? 0.0f : Value);
	}
}
