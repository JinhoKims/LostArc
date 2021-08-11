// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIProgressBar.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Components/ProgressBar.h"


void ULostArcUIProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULostArcUIProgressBar::Init(EBarType type, ALostArcCharacter *Character)
{
	ThisBarType = type;

	switch (type)
	{
	case HP:
		ProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.019f, 0.f, 1.f));
		break;
	case MP:
		ProgressBar->SetFillColorAndOpacity(FLinearColor(0.f, 0.106f, 1.f, 1.f));
		break;
	case EXP:
		ProgressBar->SetFillColorAndOpacity(FLinearColor(0.549f, 0.932f, 0.241f, 1.f));
		break;
	default:
		break;
	}

	Character->StatComponent->OnProgressBarChanged.AddUObject(this, &ULostArcUIProgressBar::UpdateProgressBar);
}

void ULostArcUIProgressBar::UpdateProgressBar()
{
	float Ratio = 0.f;

	switch (ThisBarType)
	{
	case HP:
		Ratio = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->StatComponent->GetHPRatio();
		ProgressBar->SetPercent(Ratio);
		break;
	case MP:
		Ratio = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->StatComponent->GetMPRatio();
		ProgressBar->SetPercent(Ratio);
		break;
	case EXP:
		Ratio = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->StatComponent->GetEXPRatio();
		ProgressBar->SetPercent(Ratio);
		break;
	default:
		break;
	}
}
