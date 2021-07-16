// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcPlayerSkill.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "LostArcCharacterAnimInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"


void ULostArcPlayerSkill::SetAnimInstance(ULostArcCharacterAnimInstance* Anim)
{
	Arcanim = Anim;
	PlayerCharacter = Cast<ALostArcCharacter>(Anim->TryGetPawnOwner());
	if (PlayerCharacter == nullptr) return;
}

void ULostArcPlayerSkill::SkillCast(int32 Section)
{
	bisBeingCast = true;
	switch (Section)
	{
	case 0:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		break;
	case 1:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		Arcanim->Montage_JumpToSection(TEXT("Skill_B"), Arcanim->SkillMontage);
		break;
	case 2:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		Arcanim->Montage_JumpToSection(TEXT("Skill_C"), Arcanim->SkillMontage);
		break;
	case 3:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		Arcanim->Montage_JumpToSection(TEXT("Skill_D"), Arcanim->SkillMontage);
		PlayerCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
	default:
		break;
	}
}

void ULostArcPlayerSkill::SkillHitCheck(int32 Slot)
{
	FCollisionQueryParams Params(NAME_None, false, PlayerCharacter);
	TArray<FHitResult> HitResults;
	bool bResult;
	FDamageEvent DamageEvent;
	FPointDamageEvent PointDamageEvent;
	EAttackType type;

	switch (Slot)
	{
	case 0:
		bResult = PlayerCharacter->GetWorld()->SweepMultiByChannel(HitResults, PlayerCharacter->GetActorLocation(),
			PlayerCharacter->GetActorLocation(),
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(275.f), Params);
		DrawDebugSphere(PlayerCharacter->GetWorld(), PlayerCharacter->GetActorLocation(), 275.f, 32, FColor::Cyan, false, 1.f);
		type = EAttackType::Normal;
		break;
	case 1:
		bResult = PlayerCharacter->GetWorld()->SweepMultiByChannel(HitResults, PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f,
			PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f,
			PlayerCharacter->GetActorQuat(), ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(FVector(100.f, 400.f, 50.f)), Params);
		DrawDebugBox(PlayerCharacter->GetWorld(), PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f,
			FVector(100.f, 400.f, 50.f), PlayerCharacter->GetActorQuat(), FColor::Orange, false, 1.f);
		type = EAttackType::Normal;
		break;
	case 2:
		bResult = PlayerCharacter->GetWorld()->SweepMultiByChannel(HitResults, PlayerCharacter->GetActorLocation(),
			PlayerCharacter->GetActorLocation(),
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(250.f), Params);
		DrawDebugSphere(PlayerCharacter->GetWorld(), PlayerCharacter->GetActorLocation(), 250.f, 32, FColor::Silver, false, 1.f);
		type = EAttackType::Normal;
		break;
	case 3:
		PlayerCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
		bResult = PlayerCharacter->GetWorld()->SweepMultiByChannel(HitResults, PlayerCharacter->GetActorLocation(),
			PlayerCharacter->GetActorLocation(),
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(260.f), Params);
		DrawDebugSphere(PlayerCharacter->GetWorld(), PlayerCharacter->GetActorLocation(), 260.f, 32, FColor::Purple, false, 1.f);
		type = EAttackType::Normal;
		break;
	default:
		break;
	}
	

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage handling
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			switch (type)
			{
			case EAttackType::Normal:
				hit.Actor->TakeDamage(10.0f, DamageEvent, PlayerCharacter->GetController(), PlayerCharacter);
				break;
			case EAttackType::Point:
				hit.Actor->TakeDamage(10.0f, PointDamageEvent, PlayerCharacter->GetController(), PlayerCharacter);
				break;
			case EAttackType::Radial:
				break;
			default:
				break;
			}
		}
	}

}