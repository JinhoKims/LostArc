// Copyright Epic Games, Inc. All Rights Reserved.

#include "Controller/LostArcPlayerController.h"
#include "Engine/World.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Abilities/Skill/LostArcSkillBase.h"
#include "UI/LostArcUIMainHUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ALostArcPlayerController::ALostArcPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	static ConstructorHelpers::FClassFinder<ULostArcUIMainHUD> UI_HUD_C(TEXT("WidgetBlueprint'/Game/Widget/HUD/BP_MainHUD.BP_MainHUD_C'"));
	if (UI_HUD_C.Succeeded())
	{
		MainHUDClass = UI_HUD_C.Class;
	}
}

void ALostArcPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ALostArcPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ALostArcPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("WheelUp", IE_Pressed, this, &ALostArcPlayerController::MouseWheelUp);
	InputComponent->BindAction("WheelDown", IE_Pressed, this, &ALostArcPlayerController::MouseWheelDown);
}

void ALostArcPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	MainHUD = CreateWidget<ULostArcUIMainHUD>(this, MainHUDClass);
	MainHUD->AddToViewport(1);
}

void ALostArcPlayerController::BeginPlay()
{	
}

void ALostArcPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	// Camera Situation Update
	if (bCameraSit.Key) 
	{
		CameraPositionChange(bCameraSit.Value);
	}
}

void ALostArcPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	if (!ULostArcSkillBase::bAnimationRunning)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ALostArcPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation); // Requires placement of NevmeshboundsVolume in level
		}
	}
}

void ALostArcPlayerController::MouseWheelUp()
{
	bCameraSit.Key = true;
	bCameraSit.Value = true;
	GetWorldTimerManager().ClearTimer(CameraZoomTimer);
	GetWorldTimerManager().SetTimer(CameraZoomTimer, FTimerDelegate::CreateLambda([&]() { bCameraSit.Key = false; }), 3.5f, false);
}

void ALostArcPlayerController::MouseWheelDown()
{
	bCameraSit.Key = true;
	bCameraSit.Value = false;
	GetWorldTimerManager().ClearTimer(CameraZoomTimer);
	GetWorldTimerManager().SetTimer(CameraZoomTimer, FTimerDelegate::CreateLambda([&]() { bCameraSit.Key = false; }), 3.5f, false);
}

void ALostArcPlayerController::CameraPositionChange(bool bWheel)
{
	auto ArcCharacter = Cast<ALostArcCharacter>(GetPawn());
	if (ArcCharacter == nullptr) return;
	if (bWheel)
	{
		ArcCharacter->GetCameraBoom()->TargetArmLength = FMath::Clamp(ArcCharacter->GetCameraBoom()->TargetArmLength -= 5.f, 300.f, 900.f);
		ArcCharacter->GetCameraBoom()->SetRelativeRotation(FMath::Lerp(FQuat(ArcCharacter->GetCameraBoom()->GetRelativeRotation()), FQuat(FRotator(-20.0f, 0.0f, 0.0f)), 0.03));
		ArcCharacter->GetTopDownCameraComponent()->SetFieldOfView(FMath::Clamp(ArcCharacter->GetTopDownCameraComponent()->FieldOfView += .1f, 90.f, 100.f));
	}
	else
	{
		ArcCharacter->GetCameraBoom()->TargetArmLength = FMath::Clamp(ArcCharacter->GetCameraBoom()->TargetArmLength += 5.f, 300.f, 900.f);
		ArcCharacter->GetCameraBoom()->SetRelativeRotation(FMath::Lerp(FQuat(ArcCharacter->GetCameraBoom()->GetRelativeRotation()), FQuat(FRotator(-50.0f, 0.0f, 0.0f)), 0.03));
		ArcCharacter->GetTopDownCameraComponent()->SetFieldOfView(FMath::Clamp(ArcCharacter->GetTopDownCameraComponent()->FieldOfView -= .1f, 90.f, 100.f));
	}
}
