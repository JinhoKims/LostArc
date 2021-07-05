// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CorpseAttack.h"

UBTTask_CorpseAttack::UBTTask_CorpseAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CorpseAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::InProgress; // When the task is first run
}

void UBTTask_CorpseAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // Task end condition (wait for Succeeded)
	// 태스크가 Succeeded를 반환하지 못하면 InProgress를 반환하여 다음 노드로 넘어가도록 한다.
}
