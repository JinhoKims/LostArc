// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcCharacterAbilityMelee.h"
#include "LostArcCharacter.h"
#include "LostArcCharacterAnimInstance.h"

void ULostArcCharacterAbilityMelee::ConstructAbility(float mana, float cooldown, FString name)
{
	ULostArcCharacterAbilityBase::ConstructAbility(mana, cooldown, name);
}

void ULostArcCharacterAbilityMelee::Use(ALostArcCharacter* Character)
{
	auto anim = Character->ArcanimInstance;

	anim->Montage_Play(anim->SkillMontage, 1.f);
	anim->Montage_JumpToSection(FName(*SlotName), anim->SkillMontage);
}

