// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_CorpseAttack.h"
#include "Enemy/CorpseAIController.h"
#include "Enemy/CorpseCharacter.h"
#include "AnimInstances/CorpseAnimInstance.h"
#include "LostArcCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CorpseAttack::UBTTask_CorpseAttack()
{
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_CorpseAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto CorpseCharacter = Cast<ACorpseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto CorpseAnim = Cast<UCorpseAnimInstance>(CorpseCharacter->GetMesh()->GetAnimInstance());
	if (CorpseCharacter == nullptr) return EBTNodeResult::Failed;
	if (CorpseAnim->Montage_IsPlaying(CorpseAnim->CorpseFlinchMontage) || (CorpseAnim->Montage_IsPlaying(CorpseAnim->CorpseDeathMontage))) return EBTNodeResult::Failed;

	CorpseCharacter->Attack();
	bIsAttacking = true;
	CorpseCharacter->OnAttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false; }); // 몽타주가 끝나여 브로드캐스팅 시에야 false로 전환

	return EBTNodeResult::InProgress; // When the task is first run
}

void UBTTask_CorpseAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto CorpseChar = Cast<ACorpseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto CorpseAnim = Cast<UCorpseAnimInstance>(CorpseChar->GetMesh()->GetAnimInstance());
	if (CorpseAnim->Montage_IsPlaying(CorpseAnim->CorpseFlinchMontage))
	{
		bIsAttacking = false;
	}

	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // Task end condition (wait for Succeeded)
		// 태스크가 Succeeded를 반환하지 못하면 ExcuteTask에서 InProgress를 반환하여 기다리게한다.
	}
}


