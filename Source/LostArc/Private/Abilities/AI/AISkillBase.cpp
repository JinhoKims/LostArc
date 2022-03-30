// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/AISkillBase.h"
#include "Character/MonsterCharacterBase.h"

bool UAISkillBase::bAnimationRunning = false;

bool UAISkillBase::Use(AMonsterCharacterBase* Monster)
{
	return AbilityStateCheck(Monster);
}

bool UAISkillBase::AbilityStateCheck(AMonsterCharacterBase* Monster)
{
	if(bAnimationRunning)
	{
		return false;
	}
	return true;
}
