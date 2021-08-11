// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIMainHUD.h"
#include "UI/LostArcUIAbilitySlot.h"
#include "UI/LostArcUIProgressBar.h"
#include "Character/LostArcCharacter.h"
#include "Components/ProgressBar.h"

void ULostArcUIMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 9; i++)
	{
		AbilitySlots.Add(Cast<ULostArcUIAbilitySlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_AbilitySlot_%d"), i)))));
	}

	BP_HPBAR->Init(EBarType::HP, Cast<ALostArcCharacter>(GetOwningPlayerPawn()));
	BP_MPBAR->Init(EBarType::MP, Cast<ALostArcCharacter>(GetOwningPlayerPawn()));
	BP_EXPBAR->Init(EBarType::EXP, Cast<ALostArcCharacter>(GetOwningPlayerPawn()));
}
