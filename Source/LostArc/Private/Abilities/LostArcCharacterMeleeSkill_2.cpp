// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_2.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_2::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);
}

void ULostArcCharacterMeleeSkill_2::Use(ALostArcCharacter* Character)
{
	Super::Use(Character);

	if (bAbilityAvailable)
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_2_Montage, 1.f);
	}
}

void ULostArcCharacterMeleeSkill_2::HitCheck(ALostArcCharacter* Character)
{
	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;
	FDamageEvent DamageEvent;

	GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorQuat(), ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(FVector(100.f, 400.f, 50.f)), Params);
	DrawDebugBox(GetWorld(), Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, FVector(100.f, 400.f, 50.f), Character->GetActorQuat(), FColor::Orange, false, 1.f);

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage Count
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			hit.Actor->TakeDamage(Character->StatComponent->GetAttack() * Damage_Ratio, DamageEvent, Character->GetController(), Character);
		}
	}
}
