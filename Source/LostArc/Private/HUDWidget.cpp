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

	TestImage = Cast<UImage>(GetWidgetFromName(TEXT("CicularImage_0")));


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

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CombatComponent->GetSkillAvailable(1))
	{
		float CDTime = 5.0f;
		float RemainingTime = CombatComponent->GetOwner()->GetWorldTimerManager().GetTimerRemaining(CombatComponent->GetCDTimerHandle(1));
		float Result = RemainingTime / 5.0f;
		TestImage->GetDynamicMaterial()->SetScalarParameterValue(FName(TEXT("Progress")), Result < 0.002f ? 0.0f : Result);
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
