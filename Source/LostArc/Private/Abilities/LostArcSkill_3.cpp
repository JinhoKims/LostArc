// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcSkill_3.h"

ULostArcSkill_3::ULostArcSkill_3(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 6.f;
	ManaCost = 15.f;
	SkillRatio = 1.25f;
	SkillRadius.Key = 480.f;
	SkillRadius.Value = 270.f;
}

bool ULostArcSkill_3::Use(ALostArcCharacter* Character)
{
	if (Super::Use(Character))
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_3_Montage, 1.f);
		return true;
	}
	else
		return false;
}
