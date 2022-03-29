// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MonsterAttack.h"

#include "AIController.h"
#include "AnimInstances/MonsterAnimInstanceBase.h"
#include "Character/MonsterCharacterBase.h"

UBTTask_MonsterAttack::UBTTask_MonsterAttack()
{
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MonsterCharacter = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	auto MonsterAnim = Cast<UMonsterAnimInstanceBase>(MonsterCharacter->GetMesh()->GetAnimInstance());

	if (MonsterCharacter == nullptr) return EBTNodeResult::Failed;
	if (MonsterAnim->Montage_IsPlaying(MonsterAnim->MonsterFlinchMontage) || (MonsterAnim->Montage_IsPlaying(MonsterAnim->MonsterDeathMontage))) return EBTNodeResult::Failed;

	MonsterCharacter->MonsterAttack();
	bIsAttacking = true;
	MonsterCharacter->OnAttackEnd.AddLambda([this]() -> void { bIsAttacking = false; }); // 몽타주가 끝나여 브로드캐스팅 시에야 false로 전환

	return EBTNodeResult::InProgress; // When the task is first run
}

void UBTTask_MonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto MonsterChar = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	auto MonsterAnim = Cast<UMonsterAnimInstanceBase>(MonsterChar->GetMesh()->GetAnimInstance());
	if (MonsterAnim->Montage_IsPlaying(MonsterAnim->MonsterFlinchMontage))
	{
		bIsAttacking = false;
	}

	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // Task end condition (wait for Succeeded)
		// 태스크가 Succeeded를 반환하지 못하면 ExecuteTask에서 InProgress를 반환하여 기다리게한다. bIsAttacking이 false라면 Succeeded를 반환한다.
	}
}
