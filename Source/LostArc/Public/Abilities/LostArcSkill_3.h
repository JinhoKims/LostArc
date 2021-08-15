// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcSkillBase.h"
#include "LostArcSkill_3.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class LOSTARC_API ULostArcSkill_3 : public ULostArcSkillBase
{
	GENERATED_BODY()
	
public:
	ULostArcSkill_3(const FObjectInitializer& ObjectInitializer);
	virtual bool Use( ALostArcCharacter* Character) override;
};
