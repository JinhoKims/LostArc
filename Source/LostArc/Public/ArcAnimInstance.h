// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "ArcAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate)
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate)


/**
 * 
 */
UCLASS()
class LOSTARC_API UArcAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UArcAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrviateAccess = true))
	UAnimMontage * auto_AttackMontage;

	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);
	FName GetAttackMontageSectionName(int32 Section);
};
