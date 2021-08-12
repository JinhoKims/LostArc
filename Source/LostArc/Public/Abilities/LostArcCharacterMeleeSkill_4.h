// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcCharacterAbilityBase.h"
#include "LostArcCharacterMeleeSkill_4.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcCharacterMeleeSkill_4 : public ULostArcCharacterAbilityBase
{
	GENERATED_BODY()

public:
	virtual void ConstructAbility(float mana, float cooldown, float factor) override;
	virtual void Use(class ALostArcCharacter* Character) override;
	virtual void HitCheck(class ALostArcCharacter* Character) override;
};
