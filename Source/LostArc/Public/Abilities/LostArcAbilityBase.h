// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "LostArcAbilityBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCDDelegate, bool);

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	TPair<FTimerHandle, FOnAbilityCDDelegate> AbilityCDProperty;

public:
	virtual bool Use(ALostArcCharacter* Character);
	virtual bool AbilityStateCheck(ALostArcCharacter* Character);
	float GetCDTime() { return CoolDown; }

protected:
	float CoolDown;
};
