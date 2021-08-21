// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcCharacterStatComponent.h"
#include "LostArcAbilityBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCDDelegate, bool);

/**
 * 
 */
UCLASS(Abstract)
class LOSTARC_API ULostArcAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	TPair<FTimerHandle, FOnAbilityCDDelegate> AbilityCDProperty;
	
public:
	virtual bool Use(ALostArcCharacter* Character) PURE_VIRTUAL(ULostArcAbilityBase::Use, return false;);
	virtual bool AbilityStateCheck(ALostArcCharacter* Character) PURE_VIRTUAL(ULostArcAbilityBase::AbilityStateCheck, return false;);
	float GetCDTime() { return CoolDown; }
	FString GetName() { return Name; }

protected:
	float CoolDown;
	FString Name;
};
