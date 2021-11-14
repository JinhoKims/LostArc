// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIMainHUD.h"
#include "UI/LostArcUIAbilitySlot.h"
#include "UI/LostArcUIProgressBar.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcCharacterInterface.h"
#include "Components/ProgressBar.h"
#include "UI/LostArcUISlotDrag.h"
#include "UI/Quick/LostArcUIQuickSlot.h"

void ULostArcUIMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 9; i++)
	{
		AbilitySlots.Add(Cast<ULostArcUIAbilitySlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_AbilitySlot_%d"), i)))));
	}
}