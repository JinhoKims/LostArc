// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_Charger.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MonsterCharacterBase.h"
#include "Component/AIAbilityComponent.h"
#include "Controller/MonsterBaseAIController.h"

UBTService_Charger::UBTService_Charger()
{
	NodeName = TEXT("Charger");
	Interval = 1.0f; // 서비스 호출 주기
}

void UBTService_Charger::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if(Monster == nullptr) return;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterBaseAIController::ChargeKey,  Monster->GetAbilityComponent()->GetCDProperty());
}
