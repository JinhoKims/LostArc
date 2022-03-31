// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/AISkill_1.h"

UAISkill_1::UAISkill_1(const FObjectInitializer& ObjectInitializer)
{
	DamageRatio = 3.0f;
	SkillRadius.Key = 400.f;
	SkillRadius.Value = 120.f;
	SkillType = EAbilityType::MeleeSkill_1;
}

bool UAISkill_1::Use(AMonsterCharacterBase* Monster)
{
	if(Super::Use(Monster))
	{

		return true;
	}
	else
		return false;
}
