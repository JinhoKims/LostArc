// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcCharacterAbilityBasic.h"

void ULostArcCharacterAbilityBasic::ConstructAbility(float mana, float cooldown, FString name)
{
	ULostArcCharacterAbilityBase::ConstructAbility(mana, cooldown, name);

	CurrentCombo = 0;
	MaxCombo = 3;
	AttackRange = 100.0f;
	AttackRadius = 150.0f;
}

void ULostArcCharacterAbilityBasic::Use(ALostArcCharacter* Character)
{
}

void ULostArcCharacterAbilityBasic::BasicAttackStartComboState()
{
}

void ULostArcCharacterAbilityBasic::BasicAttackEndComboState()
{
}

void ULostArcCharacterAbilityBasic::BasicAttackNextComboCheck()
{
}
