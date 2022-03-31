// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_SkillPattern.h"
#include "TimerManager.h"
#include "Character/BossMonsterCharacter.h"
#include "Component/AIAbilityComponent.h"
#include "Controller/BossMonsterAIController.h"

UBTService_SkillPattern::UBTService_SkillPattern()
{
	NodeName = TEXT("Pattern");
	Interval = 0.1f; // 서비스 호출 주기
}

void UBTService_SkillPattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto MonsterCharacter = Cast<ABossMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto Timer = MonsterCharacter->GetAbilityComponent()->AIPatternTimer;
	
	if(!MonsterCharacter->GetWorldTimerManager().IsTimerActive(Timer))
	{
		auto FTimeScale = FMath::RandRange(3.f, 8.f);
		MonsterCharacter->GetWorldTimerManager().SetTimer(Timer, FTimeScale, false);
	}
}
