// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Skill/LostArcSkill_6.h"

ULostArcSkill_6::ULostArcSkill_6(const FObjectInitializer& ObjectInitializer)
{
	CoolDown = 3.f;
	ManaCost = 40.f;
	SkillRatio = 0.5f;
	SkillRadius.Key = 150.f;
	SkillRadius.Value = 360.f;
	Skill_Type = EAbilityType::RangedSpell_2;
	Name = "Skill_6";

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_ICE_ATK(TEXT("Blueprint'/Game/BluePrint/Ability/RangedSkill/Ranged_2/BP_Ranged_Wind_Unit.BP_Ranged_Wind_Unit'"));
	if (BP_ICE_ATK.Object)
	{
		Skill_Actor = (UClass*)BP_ICE_ATK.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Indicator(TEXT("Blueprint'/Game/BluePrint/Ability/RangedSkill/Ranged_2/BP_RangedSkill_Indicator_2.BP_RangedSkill_Indicator_2'"));
	if (BP_Indicator.Object)
	{
		Skill_Indicator = (UClass*)BP_Indicator.Object->GeneratedClass;
	}
}

bool ULostArcSkill_6::Use(ALostArcPlayerCharacter* Character)
{
	if(Super::Use(Character))
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerRangedSkill_2_Montage, 1.f);
		return true;
	}
	return false;
}