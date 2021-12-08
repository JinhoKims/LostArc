// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/LostArcSkill_2.h"

ULostArcSkill_2::ULostArcSkill_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 5.f;
	ManaCost = 15.f;
	SkillRatio = 1.2f;
	SkillRadius.Key = 300.f;
	SkillRadius.Value = 160.f;
	Name = "Skill_2";
}

bool ULostArcSkill_2::Use(ALostArcPlayerCharacter* Character)
{
	if (Super::Use(Character))
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_2_Montage, 1.f);
		return true;
	}
	else
		return false;
}
