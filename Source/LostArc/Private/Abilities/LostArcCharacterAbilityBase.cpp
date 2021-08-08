// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterAbilityBase.h"
#include "LostArcCharacter.h"

void ULostArcCharacterAbilityBase::ConstructAbility(float mana, float cooldown, float ratio)
{
	ManaCost = mana;
	CoolDown = cooldown;
	Damage_Ratio = ratio;
}

void ULostArcCharacterAbilityBase::Use(ALostArcCharacter* Character)
{
}

void ULostArcCharacterAbilityBase::HitCheck(ALostArcCharacter* Character)
{
}
