// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "LostArcCharacterStatComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULostArcCharacterStatComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetNewLevel(int32 NewLevel);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

private:
	struct FArcCharacterData* CurrentStatData = nullptr;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 CurrentExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentMP;
};
