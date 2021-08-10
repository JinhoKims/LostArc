// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_3.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_3::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);
}

void ULostArcCharacterMeleeSkill_3::Use(ALostArcCharacter* Character)
{
	Super::Use(Character);

	if (bAbilityAvailable)
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_3_Montage, 1.f);
	}
}

void ULostArcCharacterMeleeSkill_3::HitCheck(ALostArcCharacter* Character)
{
	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;
	FDamageEvent DamageEvent;

	GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(250.f), Params);
	DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 250.f, 32, FColor::Silver, false, 1.f);

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage Count
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			hit.Actor->TakeDamage(Character->StatComponent->GetAttack() * Damage_Ratio, DamageEvent, Character->GetController(), Character);
		}
	}
}
