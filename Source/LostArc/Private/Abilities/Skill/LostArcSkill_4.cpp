// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/LostArcSkill_4.h"
#include "Components/CapsuleComponent.h"

ULostArcSkill_4::ULostArcSkill_4(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 8.f;
	ManaCost = 20.f;
	SkillRatio = 2.f;
	SkillRadius.Key = 600.f;
	SkillRadius.Value = 360.f;
	Name = "Skill_4";
}

bool ULostArcSkill_4::Use(ALostArcCharacter* Character)
{
	if (Super::Use(Character))
	{
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_4_Montage, 1.f);
		return true;
	}
	else
		return false;
}

void ULostArcSkill_4::HitDetection(ALostArcCharacter* Character)
{
	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));

	Super::HitDetection(Character);
}
