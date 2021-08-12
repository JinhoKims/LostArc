// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/LostArcCharacterAbilityComponent.h"
#include "Controller/LostArcPlayerController.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

#include "Abilities/LostArcCharacterAbilityBase.h"
#include "Abilities/LostArcCharacterAbilityBasic.h"
#include "Abilities/LostArcCharacterMeleeSkill_1.h"
#include "Abilities/LostArcCharacterMeleeSkill_2.h"
#include "Abilities/LostArcCharacterMeleeSkill_3.h"
#include "Abilities/LostArcCharacterMeleeSkill_4.h"
#include "Abilities/LostArcCharacterAbilityEvade.h"


// Sets default values for this component's properties
ULostArcCharacterAbilityComponent::ULostArcCharacterAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void ULostArcCharacterAbilityComponent::InitializeComponent() // 멤버 초기화는 반드시 컴포넌트 초기화에서!
{
	Super::InitializeComponent();

	Abilities.Add(NewObject<ULostArcCharacterAbilityBasic>(this));
	Abilities.Add(NewObject<ULostArcCharacterMeleeSkill_1>(this));
	Abilities.Add(NewObject<ULostArcCharacterMeleeSkill_2>(this));
	Abilities.Add(NewObject<ULostArcCharacterMeleeSkill_3>(this));
	Abilities.Add(NewObject<ULostArcCharacterMeleeSkill_4>(this));
	Abilities.Add(NewObject<ULostArcCharacterAbilityBase>(this));
	Abilities.Add(NewObject<ULostArcCharacterAbilityBase>(this));
	Abilities.Add(NewObject<ULostArcCharacterAbilityBase>(this));
	Abilities.Add(NewObject<ULostArcCharacterAbilityBase>(this));
	Abilities.Add(NewObject<ULostArcCharacterAbilityEvade>(this));

	Abilities[EAbilityType::BasicAttack]->ConstructAbility(0.f, 0.f, 1.f); // Basic Attack
	Abilities[EAbilityType::MeleeSkill_1]->ConstructAbility(10.f, 5.f, 1.5f);
	Abilities[EAbilityType::MeleeSkill_2]->ConstructAbility(15.f, 5.f, 1.2f);
	Abilities[EAbilityType::MeleeSkill_3]->ConstructAbility(15.f, 6.f, 1.25f);
	Abilities[EAbilityType::MeleeSkill_4]->ConstructAbility(20.f, 8.f, 2.f);
	Abilities[EAbilityType::RangedSpell_1]->ConstructAbility(0.f, 0.f, 1.f); // Dummy Slot
	Abilities[EAbilityType::RangedSpell_2]->ConstructAbility(0.f, 0.f, 1.f);
	Abilities[EAbilityType::RangedSpell_3]->ConstructAbility(0.f, 0.f, 1.f);
	Abilities[EAbilityType::RangedSpell_4]->ConstructAbility(0.f, 0.f, 1.f);
	Abilities[EAbilityType::Evade]->ConstructAbility(0.f, 10.f, 0.f); // Evade
}

// Called when the game starts
void ULostArcCharacterAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ULostArcCharacterAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULostArcCharacterAbilityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) // 동적 할당한 멤버를 여기서 해제해준다.
{
	Super::EndPlay(EndPlayReason);
	Abilities.Empty();
}

void ULostArcCharacterAbilityComponent::AbilityCast(EAbilityType Type)
{
	Abilities[Type]->Use(Cast<ALostArcCharacter>(GetOwner()));
}

void ULostArcCharacterAbilityComponent::AbilityHitCheck(EAbilityType Type)
{
	Abilities[Type]->HitCheck(Cast<ALostArcCharacter>(GetOwner()));
}

ULostArcCharacterAbilityBasic* ULostArcCharacterAbilityComponent::GetBasicAttackAbility()
{
	return Cast<ULostArcCharacterAbilityBasic>(Abilities[EAbilityType::BasicAttack]);
}

void ULostArcCharacterAbilityComponent::AbilityMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) // Evade
	{
		if (Montage->IsValidSectionName(TEXT("BasicAttack_1")))
		{
			GetBasicAttackAbility()->SetBasicAttacking(false);
			GetBasicAttackAbility()->BasicAttackEndComboState();
		}
		return;
	}

	if (Montage->IsValidSectionName(TEXT("BasicAttack_1")))
	{
		GetBasicAttackAbility()->SetBasicAttacking(false);
		GetBasicAttackAbility()->BasicAttackEndComboState();
	}

	if (Montage->IsValidSectionName(TEXT("Evade")))
	{
		Cast<ALostArcCharacter>(GetOwner())->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
		ULostArcCharacterAbilityBase::bAnimationRunning = false;
	}

	for (int i = 1; i < 5; i++)
	{
		Montage->IsValidSectionName(FName(FString::Printf(TEXT("MeleeSkill_%d"), i)));
		ULostArcCharacterAbilityBase::bAnimationRunning = false;
	}
}
