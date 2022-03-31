// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsAbilityOn.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API UBTDecorator_IsAbilityOn : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsAbilityOn();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
