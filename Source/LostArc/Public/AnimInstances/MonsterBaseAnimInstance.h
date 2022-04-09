// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Component/LostArcCharacterAbilityComponent.h"
#include "MonsterBaseAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterAttackHitCheckDelegate, EAbilityType)
DECLARE_MULTICAST_DELEGATE(FOnMonsterDeadCheckDelegate)

UCLASS()
class LOSTARC_API UMonsterBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
	bool bMonsterIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* MonsterFlinchMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* MonsterAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* MonsterDeathMontage;
	
	FOnMonsterAttackHitCheckDelegate OnMonsterAttackHitCheck;
	FOnMonsterDeadCheckDelegate OnMonsterDeadCheck;

	UFUNCTION()
	void AnimNotify_MonsterAttackHitCheck();

	UFUNCTION()
	void AnimNotify_MonsterDeadCheck();
	
	virtual void PlayAttackMontage();
	void PlayDeathMontage();
	void SetDeadAnim();
};
