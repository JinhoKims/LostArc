// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstances/MonsterBaseAnimInstance.h"

UMonsterBaseAnimInstance::UMonsterBaseAnimInstance()
{
	MonsterBasicAttackMontages.Init(NULL, 4);
}

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

void UMonsterBaseAnimInstance::AnimNotify_MonsterDeadCheck()
{
	OnMonsterDeadCheck.Broadcast();
}

void UMonsterBaseAnimInstance::SetDeadAnim()
{
	bMonsterIsDead = true;
}
