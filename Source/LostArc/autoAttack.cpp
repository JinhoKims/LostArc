// Fill out your copyright notice in the Description page of Project Settings.

#include "autoAttack.h"
#include "ArcAnimInstance.h"

UautoAttack::UautoAttack()
{
	MaxCombo = 3;
	AttackEndComboState();
}

void UautoAttack::SetAnimInstance(UArcAnimInstance* anim)
{
	Arcanim = anim;
	Arcanim->OnMontageEnded.AddDynamic(this, &UautoAttack::OnAttackMontageEnded);
	Arcanim->OnNextAttackCheck.AddLambda([this]()->void
		{
			bCanNextCombo = false;
			if (bIsComboInputOn)
			{
				AttackStartComboState();
				Arcanim->JumpToAttackMontageSection(CurrentCombo);
			}
		});
}

void UautoAttack::AttackStartComboState()
{
	bIsComboInputOn = false;
	bCanNextCombo = true;
	check(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void UautoAttack::AttackEndComboState()
{
	bIsComboInputOn = false;
	bCanNextCombo = false;
	CurrentCombo = 0;
}

void UautoAttack::autoAttack()
{
	if (bIsAttacking) // keep the combo
	{
		check(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (bCanNextCombo)
		{
			bIsComboInputOn = true;
		}
	}
	else // First combo
	{
		check(CurrentCombo == 0);
		AttackStartComboState();
		Arcanim->PlayAttackMontage();
		Arcanim->JumpToAttackMontageSection(CurrentCombo);
		bIsAttacking = true;
	}
}


void UautoAttack::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	check(CurrentCombo > 0);
	bIsAttacking = false;
	AttackEndComboState();
}
