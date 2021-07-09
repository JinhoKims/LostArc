// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcAnimInstance.h"

UArcAnimInstance::UArcAnimInstance() :Super() {}

void UArcAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UArcAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UArcAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UArcAnimInstance::AnimNotify_AttackHitCheck()
{	
	OnAttackHitCheck.Broadcast();
}

void UArcAnimInstance::JumpToAutoComboMontageSection(int32 NewSection)
{
	//check(Montage_IsPlaying(auto_AttackMontage));
	//Montage_JumpToSectionsEnd(TEXT("Skill_A")); // 현재 몽타주 애니메이션을 즉각 중단한다.
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UArcAnimInstance::AnimNotify_SkillAHitCheck()
{
	OnSkillHitCheck.Broadcast(0);
}

void UArcAnimInstance::AnimNotify_SkillBHitCheck()
{
	OnSkillHitCheck.Broadcast(1);
}

void UArcAnimInstance::AnimNotify_SkillCHitCheck()
{
	OnSkillHitCheck.Broadcast(2);
}

void UArcAnimInstance::AnimNotify_SkillDHitCheck()
{
	OnSkillHitCheck.Broadcast(3);
}
