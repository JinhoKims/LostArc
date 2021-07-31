// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"
#include "LostArcCharacterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_MPBar")));

	for (int i = 0; i < 4; i++)
	{
		UBorder* Border;
		Border = Cast<UBorder>(GetWidgetFromName(FName(FString::Printf(TEXT("Bdr_Slot_%d"), i))));
		if (Border)
		{
			SkillSlots.Add(Border);
			UE_LOG(LogTemp, Warning, TEXT("Yezs"));
		}
	}
	
	
}

void UHUDWidget::BindCharacterStat(ULostArcCharacterStatComponent* NewCharacterStat)
{
	CurrentCharacterStat = NewCharacterStat;
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
