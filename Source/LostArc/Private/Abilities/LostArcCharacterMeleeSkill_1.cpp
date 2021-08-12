// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_1.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_1::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);
}

void ULostArcCharacterMeleeSkill_1::Use(ALostArcCharacter* Character)
{
	Super::Use(Character);

	if (bAbilityAvailable)
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_1_Montage, 1.f);
	}
}

void ULostArcCharacterMeleeSkill_1::HitCheck(ALostArcCharacter* Character)
{
	HitResultProperty = TPairInitializer<FCollisionQueryParams, TArray<FHitResult>>(FCollisionQueryParams(NAME_None, false, Character), TArray<FHitResult>());

	GetWorld()->SweepMultiByChannel(HitResultProperty.Value, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(275.f), HitResultProperty.Key);
	//DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 275.f, 32, FColor::Cyan, false, 1.f);

	Super::HitCheck(Character);
}
