// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcPlayerSkill.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "ArcAnimInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DrawDebugHelpers.h"


void ULostArcPlayerSkill::SetAnimInstance(UArcAnimInstance* Anim)
{
	Arcanim = Anim;
	PlayerCharacter = Cast<ALostArcCharacter>(Anim->TryGetPawnOwner());
	if (PlayerCharacter == nullptr) return;
}

void ULostArcPlayerSkill::SkillCast(int32 Section)
{
	bSkillCasting = true;
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

void ULostArcPlayerSkill::SkillAHitCheck()
{
	FCollisionQueryParams Params(NAME_None, false, PlayerCharacter);
	TArray<FHitResult> HitResults;

	bool bResult = PlayerCharacter->GetWorld()->SweepMultiByChannel(HitResults, PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f,
		PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(FVector(100.f, 400.f, 50.f)), Params);

	DrawDebugBox(PlayerCharacter->GetWorld(), PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f,
		FVector(100.f, 400.f, 50.f), FQuat::Identity, FColor::Red, false, 1.f);

	for (int32 i = 0; i < HitResults.Num(); i++)
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid()) // If the hit actor is a valid
		{
			FDamageEvent DamageEvent;
			hit.Actor->TakeDamage(10.0f, DamageEvent, PlayerCharacter->GetController(), PlayerCharacter);
		}
	}
}
