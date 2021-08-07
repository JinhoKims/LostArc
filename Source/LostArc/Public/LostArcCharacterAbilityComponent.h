// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LostArcCharacterAbilityComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcCharacterAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULostArcCharacterAbilityComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AbilityCast(int32 Slot);
	void AbilityHitCheck(int32 Slot);
	void sddfs();

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

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	float AttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	TArray<class ULostArcCharacterAbilityBase*> Abilities;
};
