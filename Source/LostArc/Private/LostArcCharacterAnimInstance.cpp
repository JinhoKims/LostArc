// Fill out your copyright notice in the Description page of Project Settings.

#include "LostArcCharacterAnimInstance.h"

void ULostArcCharacterAnimInstance::AnimNotify_AttackHitCheck()
{
	OnSkillHitCheck.Broadcast(0);
}

void ULostArcCharacterAnimInstance::AnimNotify_SkillAHitCheck()
{
	OnSkillHitCheck.Broadcast(1);
}

void ULostArcCharacterAnimInstance::AnimNotify_SkillBHitCheck()
{
	OnSkillHitCheck.Broadcast(2);
}

void ULostArcCharacterAnimInstance::AnimNotify_SkillCHitCheck()
{
	OnSkillHitCheck.Broadcast(3);
}

void ULostArcCharacterAnimInstance::AnimNotify_SkillDHitCheck()
{
	OnSkillHitCheck.Broadcast(4);
}

void ULostArcCharacterAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void ULostArcCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;
}

void ULostArcCharacterAnimInstance::JumpToAutoComboMontageSection(int32 NewSection)
{
	//Montage_JumpToSectionsEnd(TEXT("Skill_A")); // 현재 몽타주 애니메이션을 즉각 중단한다.
	Montage_JumpToSection(FName(*FString::Printf(TEXT("Attack%d"), NewSection)), AttackMontage);
}