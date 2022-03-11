// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Skill/LostArcSkillBase.h"
#include "LostArcSkillBase_RangedBase.generated.h"

UENUM(BlueprintType)
enum EAbilityState
{
	Stand    UMETA(DisplayName = "Stand"),
	Focusing UMETA(DisplayName = "Focusing")
};

UCLASS()
class LOSTARC_API ULostArcSkillBase_RangedBase : public ULostArcSkillBase
{
	GENERATED_BODY()

public:
	virtual bool Use(ALostArcPlayerCharacter* Character) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Skill_Circle;

	TEnumAsByte<EAbilityState> Skill_State;
};
