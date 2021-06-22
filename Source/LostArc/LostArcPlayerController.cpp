// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArcPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "LostArcCharacter.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"

ALostArcPlayerController::ALostArcPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ALostArcPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	auto ArcCharacter = Cast<ALostArcCharacter>(GetPawn());
	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	// Camera Situation Update
	CameraSituation(bMouseWheel);
}

void ALostArcPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ALostArcPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ALostArcPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ALostArcPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ALostArcPlayerController::StopJumping);

	InputComponent->BindAction("WheelUp", IE_Pressed, this, &ALostArcPlayerController::MouseWheelUp);
	InputComponent->BindAction("WheelDown", IE_Pressed, this, &ALostArcPlayerController::MouseWheelDown);


	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ALostArcPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ALostArcPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ALostArcPlayerController::OnResetVR);
}

void ALostArcPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ALostArcPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ALostArcCharacter* MyPawn = Cast<ALostArcCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ALostArcPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
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
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ALostArcPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ALostArcPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ALostArcPlayerController::Jump()
{
	auto ArcCharacter = Cast<ALostArcCharacter>(GetPawn());
	if (ArcCharacter != nullptr)
		ArcCharacter->Jump();
}

void ALostArcPlayerController::StopJumping()
{
	auto ArcCharacter = Cast<ALostArcCharacter>(GetPawn());
	if (ArcCharacter != nullptr)
		ArcCharacter->StopJumping();
}

void ALostArcPlayerController::MouseWheelUp()
{
	bMouseWheel = true;
}

void ALostArcPlayerController::MouseWheelDown()
{
	bMouseWheel = false;
}

void ALostArcPlayerController::CameraSituation(bool bWheel)
{
	auto ArcCharacter = Cast<ALostArcCharacter>(GetPawn());
	if (ArcCharacter == nullptr) return;
	if (bWheel)
	{
		ArcCharacter->GetCameraBoom()->TargetArmLength = FMath::Clamp(ArcCharacter->GetCameraBoom()->TargetArmLength -= 4.f, 300.f, 1000.f);
		ArcCharacter->GetCameraBoom()->SetRelativeRotation(FMath::Lerp(FQuat(ArcCharacter->GetCameraBoom()->GetRelativeRotation()), FQuat(FRotator(-20.0f, 0.0f, 0.0f)), 0.01));
	}
	else
	{
		ArcCharacter->GetCameraBoom()->TargetArmLength = FMath::Clamp(ArcCharacter->GetCameraBoom()->TargetArmLength += 4.f, 300.f, 1000.f);
		ArcCharacter->GetCameraBoom()->SetRelativeRotation(FMath::Lerp(FQuat(ArcCharacter->GetCameraBoom()->GetRelativeRotation()), FQuat(FRotator(-50.0f, 0.0f, 0.0f)), 0.01));
	}
}

