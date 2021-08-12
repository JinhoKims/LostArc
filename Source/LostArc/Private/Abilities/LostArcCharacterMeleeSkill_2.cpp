// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_2.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_2::ConstructAbility(float mana, float cooldown, float factor)
{
	Super::ConstructAbility(mana, cooldown, factor);
}

void ULostArcCharacterMeleeSkill_2::Use(ALostArcCharacter* Character)
{
	Super::Use(Character);

	if (bAbilityNowAvailable)
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_2_Montage, 1.f);
	}
}

void ULostArcCharacterMeleeSkill_2::HitCheck(ALostArcCharacter* Character)
{
	HitResultProperty = TPairInitializer<FCollisionQueryParams, TArray<FHitResult>>(FCollisionQueryParams(NAME_None, false, Character), TArray<FHitResult>());

	GetWorld()->SweepMultiByChannel(HitResultProperty.Value, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorQuat(), ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(FVector(100.f, 400.f, 50.f)), HitResultProperty.Key);
	//DrawDebugBox(GetWorld(), Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, FVector(100.f, 400.f, 50.f), Character->GetActorQuat(), FColor::Orange, false, 1.f);

	Super::HitCheck(Character);
}
