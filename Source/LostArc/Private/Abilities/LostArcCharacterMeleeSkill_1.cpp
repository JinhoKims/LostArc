// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_1.h"
#include "LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "LostArcCharacterStatComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_1::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);
}

void ULostArcCharacterMeleeSkill_1::Use(ALostArcCharacter* Character)
{
	Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_1_Montage, 1.f);
}

void ULostArcCharacterMeleeSkill_1::HitCheck(ALostArcCharacter* Character)
{
	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;
	FDamageEvent DamageEvent;

	GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(275.f), Params);
	DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 275.f, 32, FColor::Cyan, false, 1.f);

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage Count
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			hit.Actor->TakeDamage(Character->StatComponent->GetAttack() * Damage_Ratio, DamageEvent, Character->GetController(), Character);
		}
	}
}
