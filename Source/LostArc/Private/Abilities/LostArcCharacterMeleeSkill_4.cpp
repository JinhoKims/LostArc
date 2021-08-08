// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_4.h"
#include "LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "LostArcCharacterStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_4::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);
}

void ULostArcCharacterMeleeSkill_4::Use(ALostArcCharacter* Character)
{
	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
	Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_4_Montage, 1.f);
}

void ULostArcCharacterMeleeSkill_4::HitCheck(ALostArcCharacter* Character)
{
	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;
	FDamageEvent DamageEvent;

	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
	GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(260.f), Params);
	DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 260.f, 32, FColor::Purple, false, 1.f);

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage Count
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			hit.Actor->TakeDamage(Character->StatComponent->GetAttack() * Damage_Ratio, DamageEvent, Character->GetController(), Character);
		}
	}
}
