// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CorpseAIController.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ACorpseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACorpseAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
};
