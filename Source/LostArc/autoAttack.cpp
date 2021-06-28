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
	auto Player = Arcanim->TryGetPawnOwner();
	Arcanim->OnMontageEnded.AddDynamic(this, &UautoAttack::OnAttackMontageEnded);
	Arcanim->OnNextAttackCheck.AddLambda([this]()->void
		{
			if (bCanNextCombo) {
				AttackStartComboState();
				Arcanim->JumpToAttackMontageSection(CurrentCombo);
				bCanNextCombo = false;
			}
		});
}

void UautoAttack::AttackStartComboState()
{
	check(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void UautoAttack::AttackEndComboState()
{
	bCanNextCombo = false;
	CurrentCombo = 0;
}

void UautoAttack::autoAttack()
{
	if (bIsAttacking) // keep the combo and waiting for animation
	{
		check(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		bCanNextCombo = true;
	}
	else // first attack
	{
		check(CurrentCombo == 0);
		AttackStartComboState();
		Arcanim->PlayAttackMontage();
		Arcanim->JumpToAttackMontageSection(CurrentCombo); // If CurretCombo is 0, it will not run
		bIsAttacking = true;
	}
}


void UautoAttack::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	check(CurrentCombo > 0);
	bIsAttacking = false;
	AttackEndComboState();
}
