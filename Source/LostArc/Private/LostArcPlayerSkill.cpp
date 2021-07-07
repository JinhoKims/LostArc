// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcPlayerSkill.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "ArcAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"


void ULostArcPlayerSkill::SetAnimInstance(UArcAnimInstance* Anim)
{
	Arcanim = Anim;
	PlayerCharacter = Cast<ALostArcCharacter>(Arcanim->TryGetPawnOwner());
	if (PlayerCharacter == nullptr) return;
}

void ULostArcPlayerSkill::SkillCast(int32 Section)
{
	if (bStillCasting) return;
	auto PCon = PlayerCharacter->GetController();
	auto PlayerController = Cast<ALostArcPlayerController>(PCon);
	if (PlayerController == nullptr) return;
	PlayerCharacter->GetMovementComponent()->StopMovementImmediately();
	
	switch (Section)
	{
	case 0:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		break;
	case 1:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		Arcanim->Montage_JumpToSection(TEXT("Skill_B"), Arcanim->SkillMontage);
		break;
	default:
		break;
	}

}