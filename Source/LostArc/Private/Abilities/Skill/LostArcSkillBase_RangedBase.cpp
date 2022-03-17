// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Skill/LostArcSkillBase_RangedBase.h"
#include "Component/LostArcCharacterAbilityComponent.h"
#include "Controller/LostArcPlayerController.h"

bool ULostArcSkillBase_RangedBase::Use(ALostArcPlayerCharacter* Character)
{
	switch (Skill_State)
	{
	case EAbilityState::Stand:
		if(AbilityStateCheck(Character))
		{
			ActivityRangedCursor(true, Character);
			return false;
		}
		break;
	case EAbilityState::Focusing:
		if(AbilityStateCheck(Character))
		{
			return Super::Use(Character); // 스킬 실행
		}
		break;
	}

	return false;
}

void ULostArcSkillBase_RangedBase::ActivityRangedCursor(bool bUse, ALostArcPlayerCharacter* Character)
{
	auto PController = Character->GetNetOwningPlayer()->GetPlayerController(GetWorld());
	auto ArcPController = Cast<ALostArcPlayerController>(PController);
	auto AComponent = Character->AbilityComponent;
	
	if(bUse)
	{
		AComponent->ResetRangedAbilitiesState(Skill_Type); // 다른 스킬 상태 초기화
		Skill_State = EAbilityState::Focusing;
		ArcPController->ChangeCursor(CircleActor); // 스킬 커서 변환
	}
	else
	{
		if(Skill_State == EAbilityState::Focusing)
		{
			Skill_State = EAbilityState::Stand;
			ArcPController->ChangeCursor(nullptr);
		}
	}
}