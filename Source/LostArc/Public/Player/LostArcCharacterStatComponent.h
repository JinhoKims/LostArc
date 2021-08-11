// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArcGameInstance.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "LostArcCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnProgressBarDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULostArcCharacterStatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage) { SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->Maxhp)); }
	void SetHP(float NewHP);
	void SetMP(float NewMP);
	
	float GetHP() { return CurrentHP; }
	float GetMP() { return CurrentMP; }
	float GetAttack() { return CurrentStatData->Attack; }

	float GetHPRatio() { return CurrentStatData->Maxhp < KINDA_SMALL_NUMBER ? 0.0f : (CurrentHP / CurrentStatData->Maxhp); }
	float GetMPRatio() { return CurrentStatData->Maxmp < KINDA_SMALL_NUMBER ? 0.0f : (CurrentMP / CurrentStatData->Maxmp); }
	float GetEXPRatio() { return CurrentStatData->Nextexp < KINDA_SMALL_NUMBER ? 0.0f : (CurrentExp / CurrentStatData->Nextexp); }

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnProgressBarDelegate OnProgressBarChanged;

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

private:
	FArcCharacterData* CurrentStatData;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 CurrentExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentMP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float ManaRegenerationPerSecond;

	UFUNCTION()
	void ManaRecovery(float amount);
};
