// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterAbilityBasic.h"
#include "LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "LostArcCharacterStatComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterAbilityBasic::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);

	bBasicAttacking = false;
	CurrentCombo = 0;
	MaxCombo = 3;
	AttackRange = 100.0f;
	AttackRadius = 150.0f;
}

void ULostArcCharacterAbilityBasic::Use(ALostArcCharacter* Character)
{
	if (bBasicAttacking) // keep the combo and waiting for animation
	{
		check(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (bCanNextCombo) {
			bIsComboInputOn = true;
		}
	}
	else				// first attack
	{
		if (AbilityStatusCheck(Character))
		{
			check(CurrentCombo == 0);
			BasicAttackStartComboState();
			Super::CharacterRotatetoCursor(Character);

			Character->AnimInstance->Montage_Play(Character->AnimInstance->BasicAttack_Montage, 1.0f);
			bBasicAttacking = true;
			bAnimationRunning = true;
		}
	}
}

void ULostArcCharacterAbilityBasic::HitCheck(ALostArcCharacter* Character)
{
	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;
	FDamageEvent DamageEvent;

	GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorLocation() + Character->GetActorForwardVector() * AttackRange, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage Count
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			hit.Actor->TakeDamage(Character->StatComponent->GetAttack() * Damage_Ratio, DamageEvent, Character->GetController(), Character);
		}
	}
}

bool ULostArcCharacterAbilityBasic::AbilityStatusCheck(ALostArcCharacter* Character)
{
	if (bAnimationRunning)
	{
		return false;
	}
	return true;
}

void ULostArcCharacterAbilityBasic::BasicAttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;
	check(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ULostArcCharacterAbilityBasic::BasicAttackEndComboState()
{
	bCanNextCombo = false;
	bIsComboInputOn = false;
	CurrentCombo = 0;
}

void ULostArcCharacterAbilityBasic::BasicAttackNextComboCheck(ALostArcCharacter* Character)
{
	if (bIsComboInputOn) 
	{
		BasicAttackStartComboState();
		Character->AnimInstance->JumpToBasicAttackMontageSection(CurrentCombo);
	}
}


