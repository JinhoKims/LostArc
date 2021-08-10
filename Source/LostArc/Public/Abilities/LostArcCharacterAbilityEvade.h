// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcCharacterAbilityBase.h"
#include "LostArcCharacterAbilityEvade.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcCharacterAbilityEvade : public ULostArcCharacterAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ConstructAbility(float mana, float cooldown, float ratio) override;
	virtual void Use(class ALostArcCharacter* Character) override;
	virtual bool AbilityStatusCheck(class ALostArcCharacter* Character) override;
};
