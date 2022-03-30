// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/AIAbilityComponent.h"
#include "Character/BossMonsterCharacter.h"

// Sets default values for this component's properties
UAIAbilityComponent::UAIAbilityComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	AbilityClass.Init(UAISkillBase::StaticClass(),5);
}

void UAIAbilityComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (int i = 0; i < 5; i++)
	{
		Abilities.Add(NewObject<UAISkillBase>(this, AbilityClass[i].Get())); // Get()은 UClass 원본 데이터(파생형)를 반환한다.
	}
}

void UAIAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAIAbilityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UAISkillBase::bAnimationRunning = false;
	Abilities.Empty();
}

void UAIAbilityComponent::BasicAttack(ABossMonsterCharacter* Monster)
{
	Abilities[EAbilityType::BasicAttack]->Use(Monster);
}

