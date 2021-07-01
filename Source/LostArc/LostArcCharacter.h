// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LostArcCharacter.generated.h"

UCLASS(Blueprintable)
class ALostArcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALostArcCharacter();
	virtual void PostInitializeComponents();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY()
	class UArcAnimInstance* ArcanimInstance;
	class UautoAttack* autoAttack;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	UFUNCTION()
	void CallOnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void CalltoautoAttack();
	void CalltoautoAttackHitCheck();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

