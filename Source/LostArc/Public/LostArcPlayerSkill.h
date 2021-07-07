// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LostArcPlayerSkill.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcPlayerSkill : public UObject
{
	GENERATED_BODY()

public:
	void SetAnimInstance(class UArcAnimInstance* Anim);
	void SkillCast(int32 Section);
	
	UPROPERTY()
	class UArcAnimInstance* Arcanim;

private:
	class ALostArcCharacter* PlayerCharacter;
	bool bStillCasting;
};
