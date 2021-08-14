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
	virtual bool Use(ALostArcCharacter* Character);
	virtual bool AbilityStateCheck(ALostArcCharacter* Character);
	virtual void CharacterRotatetoCursor(ALostArcCharacter* Character);
	virtual void HitDetection(ALostArcCharacter* Character);

protected:
	void PreCast(ALostArcCharacter* Character);
};
