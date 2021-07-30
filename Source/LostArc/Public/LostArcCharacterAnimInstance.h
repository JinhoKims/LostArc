// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LostArcCharacterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSkillHitCheckDelegate, int32)

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnSkillHitCheckDelegate OnSkillHitCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, Meta = (AllowPrviateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, Meta = (AllowPrviateAccess = true))
	UAnimMontage* SkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Evade, Meta = (AllowPrviateAccess = true))
	UAnimMontage* EvadeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrviateAccess = true))
	bool IsDead;

	UFUNCTION()
	void AnimNotify_AttackHitCheck();
	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	UFUNCTION()
	void AnimNotify_SkillAHitCheck();
	UFUNCTION()
	void AnimNotify_SkillBHitCheck();
	UFUNCTION()
	void AnimNotify_SkillCHitCheck();
	UFUNCTION()
	void AnimNotify_SkillDHitCheck();

	void NativeUpdateAnimation(float DeltaSeconds) override;
	void JumpToAutoComboMontageSection(int32 NewSection);
	void SetDeadAnim() { IsDead = true; }
};
