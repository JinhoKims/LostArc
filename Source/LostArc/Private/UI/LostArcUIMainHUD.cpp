// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIMainHUD.h"
#include "UI/LostArcUIProgressBar.h"

void ULostArcUIMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULostArcUIMainHUD::EnableWidget(ESlotType EType)
{
	switch (EType)
	{
	case ESlotType::Inven:
		BP_Inven->GetVisibility() == ESlateVisibility::Visible ? BP_Inven->SetVisibility(ESlateVisibility::Hidden) : BP_Inven->SetVisibility(ESlateVisibility::Visible); 
		break;

	case ESlotType::Equip:
		BP_Equip->GetVisibility() == ESlateVisibility::Visible ? BP_Equip->SetVisibility(ESlateVisibility::Hidden) : BP_Equip->SetVisibility(ESlateVisibility::Visible); 
		break;

	default:
		break;
	}
}
