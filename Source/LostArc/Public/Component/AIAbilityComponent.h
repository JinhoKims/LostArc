// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Skill/AI/AISkillBase.h"
#include "Components/ActorComponent.h"
#include "AIAbilityComponent.generated.h"

enum EAbilityType;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOSTARC_API UAIAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAIAbilityComponent();
	void AIAbilityCast(class AMonsterCharacterBase* Monster, bool bCharging = false);
	bool GetCDProperty() { return AIAbilityCDProperty.Value; }
	void ResetCDTimer(class AMonsterCharacterBase* Monster);
	void BackupTimer(class AMonsterCharacterBase* Monster);
	void AIAbilityHitDetection(EAbilityType Type);
	float GetBasicAttackRange();
	
protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UAISkillBase>> AbilityClass;
	
	UPROPERTY(meta = (AllowPrivateAccess = true))
	TArray<UAISkillBase*> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Indicator, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AActor>> IndicatorClass;

	TPair<FTimerHandle, bool> AIAbilityCDProperty;
	FTimerHandle BackupProperty;
};
