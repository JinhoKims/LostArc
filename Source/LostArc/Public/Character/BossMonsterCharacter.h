// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MonsterCharacterBase.h"
#include "BossMonsterCharacter.generated.h"

UCLASS()
class LOSTARC_API ABossMonsterCharacter : public AMonsterCharacterBase
{
	GENERATED_BODY()

public:
	bool bisBossJumping;
	
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
};
