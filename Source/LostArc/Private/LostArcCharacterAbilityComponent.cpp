// Fill out your copyright notice in the Description page of Project Settings.

#include "LostArcCharacterAbilityComponent.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "LostArcCharacterAnimInstance.h"
#include "LostArcCharacterStatComponent.h"
#include "LostArcCharacterAbilityBasic.h"
#include "LostArcCharacterAbilityMelee.h"
#include "LostArcCharacterAbilityRange.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
ULostArcCharacterAbilityComponent::ULostArcCharacterAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentCombo = 0;
	MaxCombo = 3;
	AttackRange = 100.0f;
	AttackRadius = 150.0f;
	// ...

	Abilities.Add(NewObject<ULostArcCharacterAbilityBasic>());
	for (int i = 1; i < 5; i++)
	{
		Abilities.Add(NewObject<ULostArcCharacterAbilityMelee>());
	}
	for (int i = 5; i < 9; i++)
	{
		Abilities.Add(NewObject<ULostArcCharacterAbilityRange>());
	}
	Abilities.Add(NewObject<ULostArcCharacterAbilityMelee>());

	Abilities[0]->ConstructAbility(0.f, 0.f, FName("Basic").ToString()); // Basic Attack
	Abilities[1]->ConstructAbility(10.f, 5.f, FName("Skill_A").ToString());
	Abilities[2]->ConstructAbility(10.f, 5.f, FName("Skill_B").ToString());
	Abilities[3]->ConstructAbility(15.f, 6.f, FName("Skill_C").ToString());
	Abilities[4]->ConstructAbility(20.f, 8.f, FName("Skill_D").ToString());
	Abilities[5]->ConstructAbility(0.f, 0.f, FName("Range_A").ToString());
	Abilities[6]->ConstructAbility(0.f, 0.f, FName("Range_B").ToString());
	Abilities[7]->ConstructAbility(0.f, 0.f, FName("Range_C").ToString());
	Abilities[8]->ConstructAbility(0.f, 0.f, FName("Range_D").ToString());
	Abilities[9]->ConstructAbility(0.f, 10.f, FName("Evade").ToString()); // Evade

}


void ULostArcCharacterAbilityComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called when the game starts
void ULostArcCharacterAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULostArcCharacterAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULostArcCharacterAbilityComponent::AbilityCast(int32 Slot)
{
	Abilities[Slot]->Use(Cast<ALostArcCharacter>(GetOwner()));
}

void ULostArcCharacterAbilityComponent::AbilityHitCheck(int32 Slot)
{
	auto Character = Cast<ALostArcCharacter>(GetOwner());
	auto Controller = Cast<ALostArcCharacter>(GetOwner())->GetController();

	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;
	FDamageEvent DamageEvent;
	float Damage;

	switch (Slot)
	{
	case 0:
		GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorLocation() + Character->GetActorForwardVector() * AttackRange, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);
		Damage = 1.f;
		break;
	case 1:
		GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(275.f), Params);
		DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 275.f, 32, FColor::Cyan, false, 1.f);
		Damage = 1.5f;
		break;
	case 2:
		GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, Character->GetActorQuat(), ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(FVector(100.f, 400.f, 50.f)), Params);
		DrawDebugBox(GetWorld(), Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f, FVector(100.f, 400.f, 50.f), Character->GetActorQuat(), FColor::Orange, false, 1.f);
		Damage = 1.f;
		break;
	case 3:
		GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(250.f), Params);
		DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 250.f, 32, FColor::Silver, false, 1.f);
		Damage = 1.25f;
		break;
	case 4:
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter")); 
		GetWorld()->SweepMultiByChannel(HitResults, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(260.f), Params);
		DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 260.f, 32, FColor::Purple, false, 1.f);
		Damage = 2.f;
		break;
	}

	for (int32 i = 0; i < HitResults.Num(); i++) // Damage Count
	{
		FHitResult hit = HitResults[i];
		if (hit.Actor.IsValid())
		{
			hit.Actor->TakeDamage(Character->StatComponent->GetAttack() * Damage, DamageEvent, Controller, Character);
		}
	}
}

