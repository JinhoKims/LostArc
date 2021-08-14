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
	ULostArcCharacterAbilityBase::bAnimationRunning = false;
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

ULostArcCharacterAbilityBase* ULostArcCharacterAbilityComponent::GetAbilites(EAbilityType Type)
{
	return Abilities[Type];
}

void ULostArcCharacterAbilityComponent::AbilityMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) // Evade
	{
		if (Montage->IsValidSectionName(TEXT("BasicAttack_1")))
		{
			Cast<ULostArcCharacterAbilityBasic>(GetAbilites(EAbilityType::BasicAttack))->SetBasicAttacking(false);
			Cast<ULostArcCharacterAbilityBasic>(GetAbilites(EAbilityType::BasicAttack))->BasicAttackEndComboState();
		}
		return;
	}

	if (Montage->IsValidSectionName(TEXT("BasicAttack_1")))
	{
		Cast<ULostArcCharacterAbilityBasic>(GetAbilites(EAbilityType::BasicAttack))->SetBasicAttacking(false);
		Cast<ULostArcCharacterAbilityBasic>(GetAbilites(EAbilityType::BasicAttack))->BasicAttackEndComboState();
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