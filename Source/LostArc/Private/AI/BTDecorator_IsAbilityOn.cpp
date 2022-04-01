// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsAbilityOn.h"
#include "Controller/MonsterBaseAIController.h"
#include "Character/MonsterCharacterBase.h"
#include "Component/AIAbilityComponent.h"

UBTDecorator_IsAbilityOn::UBTDecorator_IsAbilityOn()
{
	NodeName = TEXT("IsCharge");
}

bool UBTDecorator_IsAbilityOn::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto Monster = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	
	return Monster->GetAbilityComponent()->GetCDProperty();
}
