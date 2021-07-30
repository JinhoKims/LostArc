// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LostArcPlayerController.generated.h"

UCLASS()
class ALostArcPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALostArcPlayerController();
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UHUDWidget> HUDWidgetClass;

	UPROPERTY()
	class UHUDWidget* HUDWidget;

protected:
	/* True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed() { bMoveToMouseCursor = true; }  // set flag to keep updating destination until released
	void OnSetDestinationReleased() { bMoveToMouseCursor = false; }; // clear flag to indicate we should stop updating the destination

	/* Mouse Wheel Scroll */
	void MouseWheelUp();
	void MouseWheelDown();

private:
	/* Changing the Camera position according to the mouse wheel */
	TPair<bool, bool> bCameraSit;
	FTimerHandle CameraZoomTimer;
	void CameraPositionChange(bool bWheel);
};


