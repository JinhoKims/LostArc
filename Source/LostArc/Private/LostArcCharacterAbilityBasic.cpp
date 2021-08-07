// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcCharacterAbilityBasic.h"
#include "LostArcCharacter.h"
#include "LostArcCharacterAnimInstance.h"

void ULostArcCharacterAbilityBasic::ConstructAbility(float mana, float cooldown, FString name)
{
	ULostArcCharacterAbilityBase::ConstructAbility(mana, cooldown, name);

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
		check(CurrentCombo == 0);
		BasicAttackStartComboState();
		Character->CharacterRotatetoCursor();

		Character->ArcanimInstance->Montage_Play(Character->ArcanimInstance->AttackMontage, 1.0f);
		bBasicAttacking = true;
	}
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
	if (bIsComboInputOn) {
		BasicAttackStartComboState();
		Character->ArcanimInstance->JumpToAutoComboMontageSection(CurrentCombo);
	}
}
