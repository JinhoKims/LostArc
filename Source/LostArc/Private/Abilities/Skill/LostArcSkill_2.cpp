// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/LostArcSkill_2.h"

ULostArcSkill_2::ULostArcSkill_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 5.f;
	ManaCost = 30.f;
	SkillRatio = 0.5f;
	SkillRadius.Key = 450.f;
	SkillRadius.Value = 360.f;
	Skill_Type = EAbilityType::MeleeSkill_2;
	Name = "Skill_2";
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_AQUA_SHIELD(TEXT("Blueprint'/Game/BluePrint/Ability/RangedSkill/Shield_1/BP_Shield_Aqua.BP_Shield_Aqua'"));
	if (BP_AQUA_SHIELD.Object)
	{
		Skill_Actor = (UClass*)BP_AQUA_SHIELD.Object->GeneratedClass;
	}
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

void ULostArcSkill_2::HitDetection(ALostArcPlayerCharacter* Character)
{
	if(!IsValid(EffectState))
	{
		EffectState = GetWorld()->SpawnActor<AActor>(Skill_Actor, Character->GetActorTransform());
	}
	else
	{
		Super::HitDetection(Character);
	}
}