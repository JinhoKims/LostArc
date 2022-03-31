// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_BossPatternGenerator.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Character/BossMonsterCharacter.h"

UBTTask_BossPatternGenerator::UBTTask_BossPatternGenerator()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_BossPatternGenerator::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto MonsterCharacter = Cast<ABossMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (MonsterCharacter == nullptr) return EBTNodeResult::Failed;

	auto FTime = FMath::RandRange(3.f, 8.f);
	MonsterCharacter->GetWorldTimerManager().SetTimer(AIAbilityCDTimer, FTime, false);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_BossPatternGenerator::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	auto BossCharacter = Cast<ABossMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(!BossCharacter->GetWorldTimerManager().IsTimerActive(AIAbilityCDTimer))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); 
	}
}
