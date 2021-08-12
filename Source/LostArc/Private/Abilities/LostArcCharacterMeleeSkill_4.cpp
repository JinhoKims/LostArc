// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_4.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_4::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);
}

void ULostArcCharacterMeleeSkill_4::Use(ALostArcCharacter* Character)
{
	Super::Use(Character);

	if (bAbilityAvailable)
	{
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_4_Montage, 1.f);
	}
}

void ULostArcCharacterMeleeSkill_4::HitCheck(ALostArcCharacter* Character)
{
	HitResultProperty = TPairInitializer<FCollisionQueryParams, TArray<FHitResult>>(FCollisionQueryParams(NAME_None, false, Character), TArray<FHitResult>());

	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
	GetWorld()->SweepMultiByChannel(HitResultProperty.Value, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(260.f), HitResultProperty.Key);
	DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 260.f, 32, FColor::Purple, false, 1.f);

	Super::HitCheck(Character);
}
