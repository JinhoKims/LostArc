// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "ArcAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSkillAHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSkillBHitCheckDelegate);

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
	FOnSkillAHitCheckDelegate OnSkillAHitCehck;
	FOnSkillBHitCheckDelegate OnSkillBHitCehck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, Meta = (AllowPrviateAccess = true))
	UAnimMontage * AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, Meta = (AllowPrviateAccess = true))
	UAnimMontage * SkillMontage;

	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	UFUNCTION()
	void AnimNotify_SkillAHitCheck();

	UFUNCTION()
	void AnimNotify_SkillBHitCheck();

	void JumpToAutoComboMontageSection(int32 NewSection);
	FName GetAttackMontageSectionName(int32 Section) { check(FMath::IsWithinInclusive<int32>(Section, 1, 3)); return FName(*FString::Printf(TEXT("Attack%d"), Section)); }
};
