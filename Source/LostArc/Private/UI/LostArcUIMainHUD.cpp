// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIMainHUD.h"
#include "UI/LostArcUIAbilitySlot.h"

void ULostArcUIMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 9; i++)
	{
		AbilitySlots.Add(Cast<ULostArcUIAbilitySlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_AbilitySlot_%d"), i)))));
	}
}
