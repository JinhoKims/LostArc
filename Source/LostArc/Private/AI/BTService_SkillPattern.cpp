// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_SkillPattern.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MonsterCharacterBase.h"
#include "Component/AIAbilityComponent.h"
#include "Controller/MonsterBaseAIController.h"

UBTService_SkillPattern::UBTService_SkillPattern()
{
	NodeName = TEXT("Pattern");
	Interval = 1.0f; // 서비스 호출 주기
}

void UBTService_SkillPattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if(Monster == nullptr) return;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterBaseAIController::ChargeKey,  Monster->GetAbilityComponent()->GetCDProperty());
}
