// Fill out your copyright notice in the Description page of Project Settings.


#include "CorpseAIController.h"
#include "NavigationSystem.h"

ACorpseAIController::ACorpseAIController()
{
	RepeatInterval = 3.0f;
}

void ACorpseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ACorpseAIController::OnRepeatTimer, RepeatInterval, true);
	
}

void ACorpseAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void ACorpseAIController::OnRepeatTimer()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
}
