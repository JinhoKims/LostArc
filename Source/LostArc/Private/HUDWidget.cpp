// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"
#include "LostArcCharacterStatComponent.h"
#include "LostArcPlayerCombatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Components/Image.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_MPBar")));

	for (int i = 0; i < 5; i++)
	{
		UBorder* Border;
		UImage* Image;
		Border = Cast<UBorder>(GetWidgetFromName(FName(FString::Printf(TEXT("Bdr_Slot_%d"), i))));
		Image = Cast<UImage>(GetWidgetFromName(FName(FString::Printf(TEXT("CicularImage_%d"), i))));
		if (Border && Image)
		{
			SkillSlots.Add(Border);
			CicularImages.Add(Image);
		}
	}
	
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (int i = 0; i < 5; i++)
	{
		if (!CombatComponent->GetSkillAvailable(i))
		{
			if (i == 0) SkillSlots[i]->SetVisibility(ESlateVisibility::Visible);
			CicularImages[i]->SetVisibility(ESlateVisibility::Visible);
			float Result = CombatComponent->GetOwner()->GetWorldTimerManager().GetTimerRemaining(CombatComponent->GetCDTimerHandle(i)) / CombatComponent->GetSkillCD(i);
			CicularImages[i]->GetDynamicMaterial()->SetScalarParameterValue(FName(TEXT("Progress")), Result < 0.002f ? 0.0f : Result);
		}
	}
}

void UHUDWidget::BindCharacterStat(ULostArcCharacterStatComponent* NewCharacterStat, ULostArcPlayerCombatComponent* CombatCompo)
{
	CurrentCharacterStat = NewCharacterStat;
	CombatComponent = CombatCompo;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UHUDWidget::UpdateHPWidget);
	NewCharacterStat->OnMPChanged.AddUObject(this, &UHUDWidget::UpdateMPWidget);
}

void UHUDWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar != nullptr)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}

void UHUDWidget::UpdateMPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (MPProgressBar != nullptr)
		{
			MPProgressBar->SetPercent(CurrentCharacterStat->GetMPRatio());
		}
	}
}
