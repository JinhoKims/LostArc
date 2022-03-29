// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/MonsterAIControllerBase.h"
#include "BossMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ABossMonsterAIController : public AMonsterAIControllerBase
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
};
