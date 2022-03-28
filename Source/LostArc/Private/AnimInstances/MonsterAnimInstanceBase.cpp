// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/MonsterAnimInstanceBase.h"

void UMonsterAnimInstanceBase::PlayAttackMontage()
{
	Montage_Play(MonsterAttackMontage, 1.f);
}

void UMonsterAnimInstanceBase::PlayDeathMontage()
{
	Montage_Play(MonsterDeathMontage, 1.0f);
	TryGetPawnOwner()->SetActorEnableCollision(false);

	// MonsterBase에서 NotifyCheck로 Destroy하기
}

void UMonsterAnimInstanceBase::PlayMonsterDamageHandlingMontage(float MonsterHP)
{
	
}

void UMonsterAnimInstanceBase::AnimNotify_MonsterAttackHitCheck()
{
	OnMonsterAttackHitCheck.Broadcast();
}

void UMonsterAnimInstanceBase::AnimNotify_MonsterDeadCheck()
{
	OnMonsterDeadCheck.Broadcast();
}

void UMonsterAnimInstanceBase::SetDeadAnim()
{
	bMonsterIsDead = true;
}
