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
	void autoAttack();
	
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY()
	class UArcAnimInstance* Arcanim;

private:
	bool bIsAttacking;
	bool bIsComboInputOn;
	bool bCanNextCombo;
	int32 CurrentCombo;
	int32 MaxCombo;
};
