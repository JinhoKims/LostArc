// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/LostArcSkill_5.h"

ULostArcSkill_5::ULostArcSkill_5(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 20.f;
	ManaCost = 50.f;
	SkillRatio = 1.0f;
	SkillRadius.Key = 0.f;
	SkillRadius.Value = 0.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Skill/dm_skill_01_6.dm_skill_01_6'"));
	if (T2D_ICON.Object != NULL)
	{
		Ability_Icon = T2D_ICON.Object;
	}
	
	Name = "Skill_5";
}

bool ULostArcSkill_5::Use(ALostArcPlayerCharacter* Character)
{
	return Super::Use(Character);
}
