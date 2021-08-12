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
	virtual void ConstructAbility(float mana, float cooldown, float factor);
	virtual void Use(class ALostArcCharacter* Character);
	virtual void HitCheck(class ALostArcCharacter* Character) override;
	virtual bool AbilityStatusCheck(class ALostArcCharacter* Character) override;

	void BasicAttackStartComboState();
	void BasicAttackEndComboState();
	void BasicAttackNextComboCheck(ALostArcCharacter* Character);

	bool GetBasicAttacking() { return bBasicAttacking; }
	void SetBasicAttacking(bool bAttack) { bBasicAttacking = bAttack; }

private:
	bool bBasicAttacking;
	bool bCanNextCombo;
	bool bIsComboInputOn;
	int32 CurrentCombo;
	int32 MaxCombo;

	float AttackRange;
	float AttackRadius;
};
