// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LostArcCharacterAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcCharacterAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void ConstructAbility(float mana, float cooldown, FString name);
	virtual void Use(class ALostArcCharacter* Character);

public:
	UPROPERTY()
	float CoolDown;
	
	UPROPERTY()
	float ManaCost; 

	UPROPERTY()
	FString SlotName;
};
