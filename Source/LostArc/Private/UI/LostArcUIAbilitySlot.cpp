// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIAbilitySlot.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcCharacterAbilityComponent.h"
#include "Abilities/LostArcCharacterAbilityBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void ULostArcUIAbilitySlot::NativeConstruct()
{
	Super::NativeConstruct();
	auto Character = GetOwningPlayerPawn<ALostArcCharacter>();
	
	if (ThumbTexture2D->IsValidLowLevel())
	{
		Image_Thumb->SetBrushFromTexture(ThumbTexture2D);
		Text_ShortcutKey->SetText(KeyName);
	}

	Character->AbilityComponent->GetAbilites(SlotType)->OnAbilityhasCD.AddUObject(this, &ULostArcUIAbilitySlot::SetNativeTick);
	if (SlotType == EAbilityType::Evade) Image_ShortcutTri->SetVisibility(ESlateVisibility::Hidden);
	SetNativeTick(bEnableTick);
}

void ULostArcUIAbilitySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bEnableTick)
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
		auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());
		
		float Value = GetOwningPlayer()->GetWorldTimerManager().GetTimerRemaining(Character->AbilityComponent->GetAbilites(SlotType)->AbilityCoolDownTimer) / Character->AbilityComponent->GetAbilites(SlotType)->CoolDown;
		Image_CoolDown->GetDynamicMaterial()->SetScalarParameterValue(FName(TEXT("Progress")), Value < 0.002f ? 0.0f : Value);

		float Count = GetOwningPlayer()->GetWorldTimerManager().GetTimerRemaining(Character->AbilityComponent->GetAbilites(SlotType)->AbilityCoolDownTimer);
		Text_CDNum->SetText(FText::AsNumber(FMath::FloorToInt(Count)));
	}
}

void ULostArcUIAbilitySlot::SetNativeTick(bool CD)
{
	bEnableTick = CD;

	if (CD)
	{
		Image_CoolDown->SetVisibility(ESlateVisibility::Visible);
		Text_CDNum->SetVisibility(ESlateVisibility::Visible);
		if (SlotType == EAbilityType::Evade) SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Image_CoolDown->SetVisibility(ESlateVisibility::Hidden);
		Text_CDNum->SetVisibility(ESlateVisibility::Hidden);
		if (SlotType == EAbilityType::Evade) SetVisibility(ESlateVisibility::Hidden);
	}
}