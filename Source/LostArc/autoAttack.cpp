// Fill out your copyright notice in the Description page of Project Settings.

#include "autoAttack.h"
#include "ArcAnimInstance.h"
#include "LostArcPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UautoAttack::UautoAttack()
{
	MaxCombo = 3;
	AttackEndComboState();
}

void UautoAttack::SetAnimInstance(UArcAnimInstance* anim)
{
	Arcanim = anim;
	bCanNextCombo = false;

	Arcanim->OnNextAttackCheck.AddLambda([this]()->void
		{
			if (bIsComboInputOn) {
				AttackStartComboState();
				Arcanim->JumpToAttackMontageSection(CurrentCombo);
			}
		});
}

void UautoAttack::AttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;
	check(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void UautoAttack::AttackEndComboState()
{
	bCanNextCombo = false;
	bIsComboInputOn = false;
	CurrentCombo = 0;
}

void UautoAttack::autoAttack()
{
	auto PlayerController = Cast<ALostArcPlayerController>(Arcanim->TryGetPawnOwner()->GetController());
	auto PlayerCharacter = Cast<APawn>(Arcanim->TryGetPawnOwner());
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, PlayerCharacter->GetActorLocation());
	FHitResult Hit;

	if (bIsAttacking) // keep the combo and waiting for animation
	{
		check(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (bCanNextCombo) {
			bIsComboInputOn = true;
		}
	}
	else // first attack
	{
		// Find the angle between two points
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		float ang = FMath::Atan2(Hit.ImpactPoint.Y - PlayerCharacter->GetActorLocation().Y, Hit.ImpactPoint.X - PlayerCharacter->GetActorLocation().X) * 180 / PI;
		if (ang < 0) ang += 360;
		PlayerCharacter->SetActorRelativeRotation(FRotator(0.0f, ang, 0.0f));
		
		check(CurrentCombo == 0);
		AttackStartComboState();
		Arcanim->PlayAttackMontage();
		Arcanim->JumpToAttackMontageSection(CurrentCombo); // If CurretCombo is 0, it will not run
		bIsAttacking = true;
	}
}
