// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArcPlayerController.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "LostArcCharacter.h"
#include "autoAttack.h"
#include "ArcAnimInstance.h"
#include "LostArcPlayerSkill.h"

ALostArcPlayerController::ALostArcPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ALostArcPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	auto tempCharacter = Cast<ALostArcCharacter>(aPawn);
	tempCharacter->PlayerAutoAttack->PlayerController = Cast<ALostArcPlayerController>(aPawn->GetController());
	tempCharacter->PlayerSkillSet->PlayerController = Cast<ALostArcPlayerController>(aPawn->GetController());
}

void ALostArcPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	UE_LOG(LogTemp, Warning, TEXT("ControllerSetupInput"));

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ALostArcPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ALostArcPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("WheelUp", IE_Pressed, this, &ALostArcPlayerController::MouseWheelUp);
	InputComponent->BindAction("WheelDown", IE_Pressed, this, &ALostArcPlayerController::MouseWheelDown);

	InputComponent->BindAction("MeleeAttack", IE_Pressed, this, &ALostArcPlayerController::CalltoAttack);
	InputComponent->BindAction<FBindActionDelegate>("Skill_A", IE_Pressed, this, &ALostArcPlayerController::SkillCasting, 0);
	InputComponent->BindAction<FBindActionDelegate>("Skill_B", IE_Pressed, this, &ALostArcPlayerController::SkillCasting, 1);
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
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
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


void ALostArcPlayerController::CalltoAttack()
{
	FHitResult Hit;
	auto ArcCharacter = Cast<ALostArcCharacter>(GetCharacter());

	if (ArcCharacter != nullptr) 
	{
		if (ArcCharacter->ArcanimInstance->Montage_IsPlaying(ArcCharacter->ArcanimInstance->SkillMontage)) return;
		
		UAIBlueprintHelperLibrary::SimpleMoveToActor(this, GetCharacter());
		ArcCharacter->PlayerAutoAttack->autoAttack();
	}
}

void ALostArcPlayerController::SkillCasting(int32 slot)
{
	FHitResult Hit;
	auto ArcCharacter = Cast<ALostArcCharacter>(GetCharacter());
	
	if (ArcCharacter != nullptr) 
	{
		if (ArcCharacter->ArcanimInstance->IsAnyMontagePlaying() || ArcCharacter->PlayerSkillSet->bSkillCasting) return;
		ArcCharacter->PlayerAutoAttack->AttackEndComboState();

		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		float ang = FMath::Atan2(Hit.ImpactPoint.Y - ArcCharacter->GetActorLocation().Y, Hit.ImpactPoint.X - ArcCharacter->GetActorLocation().X) * 180 / PI;
		if (ang < 0) ang += 360;
		ArcCharacter->SetActorRelativeRotation(FRotator(0.0f, ang, 0.0f));
		
		UAIBlueprintHelperLibrary::SimpleMoveToActor(this, GetCharacter());
		ArcCharacter->PlayerSkillSet->SkillCast(slot);
	}
}


