// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Skill/LostArcSkillBase_RangedBase.h"
#include "LostArcSkill_6.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTest);

UCLASS()
class LOSTARC_API ULostArcSkill_6 : public ULostArcSkillBase_RangedBase
{
	GENERATED_BODY()

public:
	ULostArcSkill_6(const FObjectInitializer& ObjectInitializer);
	virtual bool Use(ALostArcPlayerCharacter* Character) override;
	virtual void SpawnEffect(ALostArcPlayerCharacter* Character) override;

	UPROPERTY(BlueprintAssignable,VisibleAnywhere)
	FOnTest DeleOnTEst;
};
