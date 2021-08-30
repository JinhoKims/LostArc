	// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LostArcUISlotBase.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcInventoryComponent.h"

void ULostArcUISlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	bEnableTick = false;
	SlotIndex = 0;
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

void ULostArcUISlotBase::SetNativeTick(bool CD)
{
	bEnableTick = CD;

	if (CD)
	{
		Image_CD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Image_CD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULostArcUISlotBase::RefreshSlotData(ULostArcAbilityBase* NewData)
{
	if (NewData == nullptr)
	{
		SlotData = nullptr;
		Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SlotData = NewData;
		if (SlotData->GetAbility_Icon() != nullptr)
		{
			Image_Icon->SetBrushFromTexture(SlotData->GetAbility_Icon());
			Image_Icon->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ULostArcUISlotBase::UnBindSlotData()
{
	SlotData->AbilityCDProperty.Value.Remove(AbilityCDHandle);
}