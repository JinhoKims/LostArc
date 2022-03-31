// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MonsterCharacterBase.h"
#include "Component/LostArcCharacterAbilityComponent.h"
#include "BossMonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ABossMonsterCharacter : public AMonsterCharacterBase
{
	GENERATED_BODY()

public:
	ABossMonsterCharacter();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void MonsterAttack() override;
	void MonsterAttack(EAbilityType Type);
};
