// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcAbilityBase.h"
#include "Component/LostArcCharacterAbilityComponent.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "LostArcSkillBase.generated.h"

UCLASS()
class LOSTARC_API ULostArcSkillBase : public ULostArcAbilityBase
{
	GENERATED_BODY()
	
public:
	static bool bAnimationRunning;
	
	virtual bool Use(ALostArcPlayerCharacter* Character);
	virtual bool AbilityStateCheck(ALostArcPlayerCharacter* Character);
	virtual void CharacterRotatetoCursor(ALostArcPlayerCharacter* Character);
	virtual void HitDetection(ALostArcPlayerCharacter* Character);
	TEnumAsByte<EAbilityType> GetSkillType() {return Skill_Type;}

protected:
	TPair<float, float> SkillRadius; // distance, angle
	TEnumAsByte<EAbilityType> Skill_Type;
	float SkillRatio;
	float ManaCost;
	
	virtual void PreCast(ALostArcPlayerCharacter* Character);
	
};
