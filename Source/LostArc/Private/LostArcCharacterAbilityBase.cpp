// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcCharacterAbilityBase.h"

void ULostArcCharacterAbilityBase::ConstructAbility(float mana, float cooldown, FString name)
{
	ManaCost = mana;
	CoolDown = cooldown;
	SlotName = name;
}

void ULostArcCharacterAbilityBase::Use(ALostArcCharacter* Character)
{

}