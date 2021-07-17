// Fill out your copyright notice in the Description page of Project Settings.

#include "LostArcPlayerCombatComponent.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "LostArcCharacterAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
ULostArcPlayerCombatComponent::ULostArcPlayerCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// reset Basic Attack factors
	CurrentCombo = 0;
	MaxCombo = 3;
	AttackRange = 100.0f;
	AttackRadius = 150.0f;
}

// Called when the game starts
void ULostArcPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
// Called every frame
void ULostArcPlayerCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULostArcPlayerCombatComponent::SkillCast(int32 Slot)
{
	auto Character = Cast<ALostArcCharacter>(GetOwner());
	auto Arcanim = Cast<ALostArcCharacter>(GetOwner())->ArcanimInstance;
	if (Character == nullptr || Arcanim == nullptr) return;
	bSkillCasting = true;

	switch (Slot)
	{
	case 0: // Basic attack
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

			Arcanim->Montage_Play(Arcanim->AttackMontage, 1.0f);
			bBasicAttacking = true;
		}
		break;
	case 1:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		break;
	case 2:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		Arcanim->Montage_JumpToSection(TEXT("Skill_B"), Arcanim->SkillMontage);
		break;
	case 3:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		Arcanim->Montage_JumpToSection(TEXT("Skill_C"), Arcanim->SkillMontage);
		break;
	case 4:
		Arcanim->Montage_Play(Arcanim->SkillMontage, 1.f);
		Arcanim->Montage_JumpToSection(TEXT("Skill_D"), Arcanim->SkillMontage);
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
		break;
	}
}

void ULostArcPlayerCombatComponent::SkillHitCheck(int32 Slot)
{
	auto Character = Cast<ALostArcCharacter>(GetOwner());
	auto Controller = Cast<ALostArcCharacter>(GetOwner())->GetController();
	if (Character == nullptr || Controller == nullptr) return;

	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;
	bool bResult;
	FDamageEvent DamageEvent;
	FPointDamageEvent PointDamageEvent;
	EAttackTypes type;

	switch (Slot)
	{
	case 0:
		bResult = GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f,
			Character->GetActorLocation() + Character->GetActorForwardVector() * AttackRange,
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);
		type = EAttackTypes::Normal;
		break;
	case 1:
		bResult = GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(),
			Character->GetActorLocation(),
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(275.f), Params);
		DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 275.f, 32, FColor::Cyan, false, 1.f);
		type = EAttackTypes::Normal;
		break;
	case 2:
		bResult = GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f,
			Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f,
			Character->GetActorQuat(), ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(FVector(100.f, 400.f, 50.f)), Params);
		DrawDebugBox(GetWorld(), Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f,
			FVector(100.f, 400.f, 50.f), Character->GetActorQuat(), FColor::Orange, false, 1.f);
		type = EAttackTypes::Normal;
		break;
	case 3:
		bResult = GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(),
			Character->GetActorLocation(),
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(250.f), Params);
		DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 250.f, 32, FColor::Silver, false, 1.f);
		type = EAttackTypes::Normal;
		break;
	case 4:
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
		bResult = GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(),
			Character->GetActorLocation(),
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(260.f), Params);
		DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 260.f, 32, FColor::Purple, false, 1.f);
		type = EAttackTypes::Normal;
		break;
	}

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage handling
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			switch (type)
			{
			case EAttackTypes::Normal:
				hit.Actor->TakeDamage(10.0f, DamageEvent, Controller, Character);
				break;
			case EAttackTypes::Point:
				hit.Actor->TakeDamage(10.0f, PointDamageEvent, Controller, Character);
				break;
			case EAttackTypes::Radial:
				break;
			default:
				break;
			}
		}
	}
}

void ULostArcPlayerCombatComponent::BasicAttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;
	check(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ULostArcPlayerCombatComponent::BasicAttackEndComboState()
{
	bCanNextCombo = false;
	bIsComboInputOn = false;
	CurrentCombo = 0;
}

void ULostArcPlayerCombatComponent::BasicAttackNextComboCheck()
{
	if (bIsComboInputOn) {
		BasicAttackStartComboState();
		auto Character = Cast<ALostArcCharacter>(GetOwner())->ArcanimInstance;
		Character->JumpToAutoComboMontageSection(CurrentCombo);
	}
}

