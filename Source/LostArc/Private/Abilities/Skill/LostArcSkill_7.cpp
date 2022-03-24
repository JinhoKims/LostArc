// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/LostArcSkill_7.h"

ULostArcSkill_7::ULostArcSkill_7(const FObjectInitializer& ObjectInitializer)
{
	CoolDown = 1.f;
	ManaCost = 30.f;
	SkillRatio = 0.5f;
	SkillRadius.Key = 500.f;
	SkillRadius.Value = 360.f;
	Skill_Type = EAbilityType::RangedSpell_3;
	Name = "Skill_7";

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_ICE_ATK(TEXT("Blueprint'/Game/BluePrint/Ability/RangedSkill/Ranged_3/BP_Ranged_Light_Unit.BP_Ranged_Light_Unit'"));
	if (BP_ICE_ATK.Object)
	{
		Skill_Actor = (UClass*)BP_ICE_ATK.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Indicator(TEXT("Blueprint'/Game/BluePrint/Ability/RangedSkill/Ranged_3/BP_RangedSkill_Indicator_3.BP_RangedSkill_Indicator_3'"));
	if (BP_Indicator.Object)
	{
		Skill_Indicator = (UClass*)BP_Indicator.Object->GeneratedClass;
	}
}

bool ULostArcSkill_7::Use(ALostArcPlayerCharacter* Character)
{
	if(Super::Use(Character))
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerRangedSkill_3_Montage, 1.f);
		return true;
	}
	return false;
}
