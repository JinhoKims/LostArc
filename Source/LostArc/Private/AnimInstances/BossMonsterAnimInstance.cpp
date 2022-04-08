// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstances/BossMonsterAnimInstance.h"

UBossMonsterAnimInstance::UBossMonsterAnimInstance()
{
	BossBasicAttackMontages.Init(NULL, 3);
}

void UBossMonsterAnimInstance::PlayAttackMontage()
{
	auto Number = FMath::RandRange(0, GetBasicAttackStep() - 1);
	Montage_Play(BossBasicAttackMontages[Number], 1.f);
}

int32 UBossMonsterAnimInstance::GetBasicAttackStep()
{
	return BossBasicAttackMontages.Num();
}

void UBossMonsterAnimInstance::AnimNotify_MonsterJumpCheck()
{
	UE_LOG(LogTemp,Warning,TEXT("AAASD"));
	OnMonsterEffectCheckDelegate.Broadcast(EAbilityType::MeleeSkill_4);
}

TArray<UAnimMontage*> UBossMonsterAnimInstance::GetBossBasicAttackMontages()
{
	return BossBasicAttackMontages;
}
