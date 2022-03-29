// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTDecorator_IsInAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/LostArcPlayerCharacter.h"
#include "Controller/MonsterBaseAIController.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return false;

	auto Target = Cast<ALostArcPlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterBaseAIController::TargetKey)); // 타겟키 정보를 Owner 비헤비어트리의 블랙보드에서 가져옴
	if (Target == nullptr) return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 300.0f); 
	return bResult;
}