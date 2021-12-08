// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LostArcCharacterAnimInstance.generated.h"

enum EAbilityType;

DECLARE_MULTICAST_DELEGATE(FOnNextBasicAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMeleeSkillHitCheckDelegate, EAbilityType);

UCLASS()
class LOSTARC_API ULostArcCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	FOnNextBasicAttackCheckDelegate OnNextBasicAttackCheck;
	FOnMeleeSkillHitCheckDelegate OnMeleeSkillHitCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
	UAnimMontage* BasicAttack_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
	UAnimMontage* Evade_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
	UAnimMontage* PlayerMeleeSkill_1_Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
	UAnimMontage* PlayerMeleeSkill_2_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
	UAnimMontage* PlayerMeleeSkill_3_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
	UAnimMontage* PlayerMeleeSkill_4_Montage;


	UFUNCTION()
	void AnimNotify_Next_BasicAttackCheck();
	UFUNCTION()
	void AnimNotify_BasicAttack_HitCheck();

	UFUNCTION()
	void AnimNotify_MeleeSkill_1_HitCheck();
	UFUNCTION()
	void AnimNotify_MeleeSkill_2_HitCheck();
	UFUNCTION()
	void AnimNotify_MeleeSkill_3_HitCheck();
	UFUNCTION()
	void AnimNotify_MeleeSkill_4_HitCheck();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void JumpToBasicAttackMontageSection(int32 NewSection);
	void SetDeadAnim() { bIsDead = true; }
};
