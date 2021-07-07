// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "autoAttack.generated.h"

/**
 * that is responsible for the default attack of the character.
 */
UCLASS()
class LOSTARC_API UautoAttack : public UObject
{
	GENERATED_BODY()

public:
	UautoAttack();
	void SetAnimInstance(class UArcAnimInstance*);
	void AttackStartComboState();
	void AttackEndComboState();
	void OnAttackMontageEnded();
	void autoAttack();
	void autoAttackHitCheck();

	UPROPERTY()
	class UArcAnimInstance* Arcanim;
	class ALostArcPlayerController* PlayerController;
	class ALostArcCharacter* PlayerCharacter;

private:
	bool bIsAttacking;
	bool bCanNextCombo;
	bool bIsComboInputOn;
	int32 CurrentCombo;
	int32 MaxCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	float AttackRadius;
};
