// Fill out your copyright notice in the Description page of Project Settings.

#include "LostArcCharacterAbilityComponent.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "LostArcCharacterStatComponent.h"
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


	Abilities[0]->ConstructAbility(0.f, 0.f, 1.f); // Basic Attack
	Abilities[1]->ConstructAbility(10.f, 5.f, 1.5f);
	Abilities[2]->ConstructAbility(12.f, 5.f, 1.2f);
	Abilities[3]->ConstructAbility(15.f, 6.f, 1.25f);
	Abilities[4]->ConstructAbility(20.f, 8.f, 2.f);
	Abilities[5]->ConstructAbility(0.f, 0.f, 1.f); // Dummy Slot
	Abilities[6]->ConstructAbility(0.f, 0.f, 1.f);
	Abilities[7]->ConstructAbility(0.f, 0.f, 1.f);
	Abilities[8]->ConstructAbility(0.f, 0.f, 1.f);
	Abilities[9]->ConstructAbility(0.f, 10.f, 0.f); // Evade
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

void ULostArcCharacterAbilityComponent::AbilityCast(int32 Slot)
{
	Abilities[Slot]->Use(Cast<ALostArcCharacter>(GetOwner()));
}

void ULostArcCharacterAbilityComponent::AbilityHitCheck(int32 Slot)
{
	Abilities[Slot]->HitCheck(Cast<ALostArcCharacter>(GetOwner()));
}

