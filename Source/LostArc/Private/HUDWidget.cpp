// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"
#include "LostArcCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_MPBar")));

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
