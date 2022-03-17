// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/LostArcSkill_5.h"

ULostArcSkill_5::ULostArcSkill_5(const FObjectInitializer& ObjectInitializer)
{
	CoolDown = 10.f;
	ManaCost = 30.f;
	SkillRatio = 1.f;
	Name = "Skill_5";

	
}

bool ULostArcSkill_5::Use(ALostArcPlayerCharacter* Character)
{
	return Super::Use(Character);
}
