// Fill out your copyright notice in the Description page of Project Settings.

#include "CorpseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"

const FName ACorpseAIController::HomePosKey(TEXT("HomePos"));
const FName ACorpseAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ACorpseAIController::TargetKey(TEXT("Target"));

ACorpseAIController::ACorpseAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/ArcCharacter/Corpse/AI/BB_Corpse.BB_Corpse'"));
	if (BBObject.Succeeded()) { BBAsset = BBObject.Object; }
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/ArcCharacter/Corpse/AI/BT_Corpse.BT_Corpse'"));
	if (BTObject.Succeeded()) { BTAsset = BTObject.Object; }
}

void ACorpseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (UseBlackboard(BBAsset, Blackboard)) // create a Blackboard component
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation()); // HomePosKey is current position of Pawn
		if (!RunBehaviorTree(BTAsset)) // create a BehaviorTree component
		{
			UE_LOG(LogTemp, Error, TEXT("AIController couldn't run Behavior tree!"));
		}
	}
}

void ACorpseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACorpseAIController::OnRepeatTimer()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation NavLoctaion;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NavLoctaion))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NavLoctaion.Location);
	}
}
