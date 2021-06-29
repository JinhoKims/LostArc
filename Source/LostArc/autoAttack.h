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

	UFUNCTION()
	void autoAttack();

	UPROPERTY()
	class UArcAnimInstance* Arcanim;

public:
	bool bIsAttacking;
	int32 CurrentCombo;

private:
	bool bCanNextCombo;
	bool bIsComboInputOn;
	int32 MaxCombo;
};
