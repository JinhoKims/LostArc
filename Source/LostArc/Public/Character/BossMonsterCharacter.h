// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MonsterCharacterBase.h"
#include "BossMonsterCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonsterSkillEffectCheckDelegate, EAbilityType, Type);

UCLASS()
class LOSTARC_API ABossMonsterCharacter : public AMonsterCharacterBase
{
	GENERATED_BODY()

public:
	bool bBossJump;
	
	ABossMonsterCharacter();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterJumpEffect();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterMeteorEffect();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterBreathEffect();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AActor>> IndicatorClass;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	FOnMonsterSkillEffectCheckDelegate OnMonsterSkillEffectCheckDelegate;
};
