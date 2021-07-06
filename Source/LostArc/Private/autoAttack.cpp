// Fill out your copyright notice in the Description page of Project Settings.

#include "autoAttack.h"
#include "ArcAnimInstance.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DrawDebugHelpers.h"


UautoAttack::UautoAttack()
{
	MaxCombo = 3;
	AttackEndComboState();

	AttackRange = 100.0f;
	AttackRadius = 150.0f;	
}

void UautoAttack::SetAnimInstance(UArcAnimInstance* anim)
{
	Arcanim = anim;
	PlayerCharacter = Cast<ALostArcCharacter>(Arcanim->TryGetPawnOwner());
	if (PlayerCharacter == nullptr) return;
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
	auto PCon = PlayerCharacter->GetController();
	auto PlayerController = Cast<ALostArcPlayerController>(PCon);
	if (PlayerController == nullptr) return;

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

void UautoAttack::autoAttackHitCheck()
{
	FCollisionQueryParams Params(NAME_None, false, PlayerCharacter);
	TArray<FHitResult> HitResults;

	bool bResult = PlayerCharacter->GetWorld()->SweepMultiByChannel(HitResults, PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f,
	PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * AttackRange,
	FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);
	
	for (int32 i = 0; i < HitResults.Num(); i++)
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid()) // If the hit actor is a valid
		{
			FDamageEvent DamageEvent;
			hit.Actor->TakeDamage(10.0f, DamageEvent, PlayerCharacter->GetController(), PlayerCharacter);
		}
	}

//FHitResult HitResult;
//bool bResult = PlayerCharacter->GetWorld()->SweepSingleByChannel(HitResult, PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f, 
//PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * AttackRange,
//FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);
//if (bResult)
//{
//	if (HitResults.Actor.IsValid()) // If the hit actor is valid
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
//		
//		FDamageEvent DamageEvent;
//		HitResult.Actor->TakeDamage(50.0f, DamageEvent, PlayerCharacter->GetController(), PlayerCharacter);
//	}
//}
//
//#if ENABLE_DRAW_DEBUG
//
//	FVector TraceVec = PlayerCharacter->GetActorForwardVector() * AttackRange;
//	FVector Center = (PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f) + TraceVec * 0.5f; // 끝 점에서 0.5를 곱해주면 중심점이 된다.
//	
//	float HalfHeight = AttackRange * 0.5f + AttackRadius; 
//	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
//	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
//	float DebugLifeTime = 1.0f;
//
//	DrawDebugCapsule(PlayerCharacter->GetWorld(), Center, HalfHeight, AttackRadius, CapsuleRot, DrawColor, false, DebugLifeTime);
//#endif
}

void UautoAttack::OnAttackMontageEnded()
{
	//check(autoAttack->bIsAttacking);
	check(CurrentCombo > 0);
	bIsAttacking = false;
	AttackEndComboState();
}