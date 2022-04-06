// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/AI/AISkillBase.h"
#include "Character/MonsterCharacterBase.h"

bool UAISkillBase::bAnimationRunning = false;

bool UAISkillBase::Use(AMonsterCharacterBase* Monster)
{
	if(AbilityStateCheck(Monster))
	{
		if(Skill_Indicator != nullptr)
		{
			auto Transform = Monster->GetMesh()->GetComponentTransform();
			Transform.SetRotation(Monster->GetActorRotation().Quaternion());
			
			GetWorld()->SpawnActor<AActor>(Skill_Indicator, Transform);
		}
		return true;
	}
	else
	{
		return false;
	}

	
}

bool UAISkillBase::AbilityStateCheck(AMonsterCharacterBase* Monster)
{
	if(bAnimationRunning)
	{
		return false;
	}
	return true;
}

void UAISkillBase::SetIndicator(TSubclassOf<AActor> Indicator)
{
	if(Indicator != nullptr)
	{
		Skill_Indicator = Indicator;
	}
}
