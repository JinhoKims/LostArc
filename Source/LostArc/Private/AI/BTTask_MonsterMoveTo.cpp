// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MonsterMoveTo.h"

UBTTask_MonsterMoveTo::UBTTask_MonsterMoveTo()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
	
}

void UBTTask_MonsterMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
