// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcAbilityBase.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "LostArcSkillBase.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcSkillBase : public ULostArcAbilityBase
{
	GENERATED_BODY()
	
public:
	static bool bAnimationRunning;
	
protected:
	TPair<float, float> SkillRadius; // distance, angle
	float SkillRatio;
	float ManaCost;

public:
	virtual bool Use(ALostArcPlayerCharacter* Character);
	virtual bool AbilityStateCheck(ALostArcPlayerCharacter* Character);
	virtual void CharacterRotatetoCursor(ALostArcPlayerCharacter* Character);
	virtual void HitDetection(ALostArcPlayerCharacter* Character);

protected:
	virtual void PreCast(ALostArcPlayerCharacter* Character);
};
