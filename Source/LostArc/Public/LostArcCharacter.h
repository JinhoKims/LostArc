// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LostArcCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FBindActionDelegate, int32)
DECLARE_DELEGATE_OneParam(FBindAbilityDelegate, int32)

UCLASS(Blueprintable)
class ALostArcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALostArcCharacter();
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class ULostArcPlayerCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class ULostArcCharacterStatComponent* StatComponent;

	UPROPERTY()
	class ULostArcCharacterAnimInstance* ArcanimInstance;

	/* Rotate the character in the direction the cursor is pointing */
	void CharacterRotatetoCursor();

	/* Player Evasion action */
	void Evade();

	/* Player Combat Actions */
	void CalltoSkillCast(int32 Slot);

	/* Functions that bind to the AnimInstnace delegate */
	UFUNCTION()
	void CallOnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

	bool bEvading;
};

