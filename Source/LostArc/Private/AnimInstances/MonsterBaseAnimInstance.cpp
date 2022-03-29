// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstances/MonsterBaseAnimInstance.h"

void UMonsterBaseAnimInstance::PlayAttackMontage()
{
	Montage_Play(MonsterAttackMontage, 1.f);
}

void UMonsterBaseAnimInstance::PlayDeathMontage()
{
	Montage_Play(MonsterDeathMontage, 1.0f);
	TryGetPawnOwner()->SetActorEnableCollision(false);

	// MonsterBase에서 NotifyCheck로 Destroy하기
}

void UMonsterBaseAnimInstance::PlayMonsterDamageHandlingMontage(float MonsterHP)
{
}

void UMonsterBaseAnimInstance::AnimNotify_MonsterAttackHitCheck()
{
	OnMonsterAttackHitCheck.Broadcast();
}

void UMonsterBaseAnimInstance::AnimNotify_MonsterDeadCheck()
{
	OnMonsterDeadCheck.Broadcast();
}

void UMonsterBaseAnimInstance::SetDeadAnim()
{
	bMonsterIsDead = true;
}