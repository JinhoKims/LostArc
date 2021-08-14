// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcSkill_Dodge.h"
#include "Components/CapsuleComponent.h"

ULostArcSkill_Dodge::ULostArcSkill_Dodge(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 10.f;
	ManaCost = 0.f;
	SkillRatio = 0.f;
	SkillRadius.Key = 0.f;
	SkillRadius.Value = 0.f;
}

bool ULostArcSkill_Dodge::Use(ALostArcCharacter* Character)
{
	if (AbilityStateCheck(Character))
	{
		PreCast(Character);
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
		Character->AnimInstance->Montage_Play(Character->AnimInstance->Evade_Montage, 1.f);
		return true;
	}
	else
		return false;
}

bool ULostArcSkill_Dodge::AbilityStateCheck(ALostArcCharacter* Character)
{
	if (Character->GetWorldTimerManager().IsTimerActive(AbilityCDProperty.Key))
	{
		UE_LOG(LogTemp, Warning, TEXT("CoolDown Left is : %f"), Character->GetWorldTimerManager().GetTimerRemaining(AbilityCDProperty.Key));
		return false;
	}
	if (Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::MP) < ManaCost)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Mana is : %f"), Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::MP));
		return false;
	}
	return true;
}
