// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArcCharacterAbilityBase.h"
#include "LostArcCharacterAbilityMelee.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcCharacterAbilityMelee : public ULostArcCharacterAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ConstructAbility(float mana, float cooldown, FString name) override;
	virtual void Use(class ALostArcCharacter* Character) override;
};
