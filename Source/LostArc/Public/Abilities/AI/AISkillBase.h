// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AISkillBase.generated.h"

UCLASS()
class LOSTARC_API UAISkillBase : public UObject
{
	GENERATED_BODY()

public:
	static bool bAnimationRunning;
	
	virtual bool Use(class AMonsterCharacterBase* Monster);
	virtual bool AbilityStateCheck(class AMonsterCharacterBase* Monster);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Skill_Effect;

	TPair<float, float> SkillRadius; // Distance, Angle
	float DamageRatio;
};
