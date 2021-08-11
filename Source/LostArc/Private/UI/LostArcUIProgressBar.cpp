// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIProgressBar.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"



void ULostArcUIProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressBar->SetFillColorAndOpacity(FLinearColor(BarColor.R, BarColor.G, BarColor.B));
	ProgressBar->SetRenderShear(BarShearValue);
	ProgressBar->SetRenderScale(BarRenderScale);
}

void ULostArcUIProgressBar::Init(ALostArcCharacter *Character)
{
	switch (BarType)
	{
	case HP:
		CurrentText->SetText(FText::AsNumber(Character->StatComponent->GetCurrentHP()));
		MaxText->SetText(FText::AsNumber(Character->StatComponent->GetMaxHP()));
		break;
	case MP:
		CurrentText->SetText(FText::AsNumber(Character->StatComponent->GetCurrentMP()));
		MaxText->SetText(FText::AsNumber(Character->StatComponent->GetMaxMP()));
		break;
	case EXP:
		ProgressBar->SetPercent(0.5f);
		CurrentText->SetVisibility(ESlateVisibility::Hidden);
		SlashText->SetVisibility(ESlateVisibility::Hidden);
		MaxText->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:
		break;
	}

	EAttributeType AType = EAttributeType::ATK;
	switch (AType)
	{
	case HP_X:
		break;
	case MP_X:
		break;
	case ATK:
		break;
	case DEF:
		break;
	case EXP_X:
		break;
	case LVL:
		break;
	default:
		break;
	}

	Character->StatComponent->OnProgressBarChanged.AddUObject(this, &ULostArcUIProgressBar::UpdateProgressBar);
}

void ULostArcUIProgressBar::UpdateProgressBar(EBarType Type)
{
	if (BarType == Type)
	{
		auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());
		float Ratio = 0.f;

		switch (BarType)
		{
		case HP:
			Ratio = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->StatComponent->GetHPRatio();
			CurrentText->SetText(FText::AsNumber(Character->StatComponent->GetCurrentHP()));
			MaxText->SetText(FText::AsNumber(Character->StatComponent->GetMaxHP()));
			ProgressBar->SetPercent(Ratio);
			break;
		case MP:
			Ratio = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->StatComponent->GetMPRatio();
			CurrentText->SetText(FText::AsNumber(Character->StatComponent->GetCurrentMP()));
			MaxText->SetText(FText::AsNumber(Character->StatComponent->GetMaxMP()));
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
}
