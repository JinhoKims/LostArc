// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossPatternGenerator.generated.h"

UCLASS()
class LOSTARC_API UBTTask_BossPatternGenerator : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BossPatternGenerator();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FTimerHandle AIAbilityCDTimer;
};
