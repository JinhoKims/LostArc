// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArcCharacterAbilityBase.h"
#include "LostArcCharacterAbilityBasic.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcCharacterAbilityBasic : public ULostArcCharacterAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ConstructAbility(float mana, float cooldown, FString name);
	virtual void Use(class ALostArcCharacter* Character);
	
	void BasicAttackStartComboState();
	void BasicAttackEndComboState();
	void BasicAttackNextComboCheck();

private:
	bool bCanNextCombo;
	bool bIsComboInputOn;
	int32 CurrentCombo;
	int32 MaxCombo;

	float AttackRange;
	float AttackRadius;
};
