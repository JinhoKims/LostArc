// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/LostArcSkill_8.h"

ULostArcSkill_8::ULostArcSkill_8(const FObjectInitializer& ObjectInitializer)
{
	CoolDown = 3.f;
	ManaCost = 20.f;
	SkillRatio = 1.25f;
	SkillRadius.Key = 400.f;
	SkillRadius.Value = 120.f;
	Skill_Type = EAbilityType::RangedSpell_4;
	Name = "Skill_8";
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Indicator(TEXT("Blueprint'/Game/BluePrint/Ability/RangedSkill/Ranged_4/BP_RangedSkill_Indicator_4.BP_RangedSkill_Indicator_4'"));
	if (BP_Indicator.Object)
	{
		Skill_Indicator = (UClass*)BP_Indicator.Object->GeneratedClass;
	}
}

bool ULostArcSkill_8::Use(ALostArcPlayerCharacter* Character)
{
	if(Super::Use(Character))
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerRangedSkill_4_Montage, 1.f);
		return true;
	}
	return false;
}

void ULostArcSkill_8::SpawnEffect(ALostArcPlayerCharacter* Character)
{
	Super::Super::HitDetection(Character); // 조부모 함수 호출
}
