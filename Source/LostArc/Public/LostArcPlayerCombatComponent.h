// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LostArcPlayerCombatComponent.generated.h"

UENUM()
enum class EAttackTypes
{
	Normal,
	Point,
	Radial,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcPlayerCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULostArcPlayerCombatComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SkillCast(int32 Slot);
	void SkillHitCheck(int32 Slot);
	bool bSkillCasting;
	bool bBasicAttacking;

	void BasicAttackStartComboState();
	void BasicAttackEndComboState();
	void BasicAttackNextComboCheck();
	bool& GetEvadeAvailable() { return SkillAvailable[0]; }
	FTimerHandle& GetEvadeCoolDownTimer() { return SkillCoolDownTimer[0]; }
	FTimerHandle& GetCDTimerHandle(int32 index) { return SkillCoolDownTimer[index]; }
	bool GetSkillAvailable(int32 index) { return SkillAvailable[index]; }
	float GetSkillCD(float index) { return SkillCD[index]; }

protected:
	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

private:
	// Basic attack variables
	bool bCanNextCombo;
	bool bIsComboInputOn;
	int32 CurrentCombo;
	int32 MaxCombo;

	TArray<bool> SkillAvailable;
	TArray<FTimerHandle> SkillCoolDownTimer;
	TArray<float> SkillCD;

	float AttackRange;
	float AttackRadius;

	bool CharacterManaCheck(float Mana);
};
