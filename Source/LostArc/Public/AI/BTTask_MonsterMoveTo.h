// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MonsterMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API UBTTask_MonsterMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_MonsterMoveTo();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
