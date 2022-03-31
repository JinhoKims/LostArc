// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/AIAbilityComponent.h"
#include "TimerManager.h"
#include "Character/BossMonsterCharacter.h"
#include "Character/LostArcPlayerCharacter.h"
#include "Controller/BossMonsterAIController.h"

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

	auto Monster = Cast<ABossMonsterCharacter>(GetOwner());
	ResetCDTimer(Monster);
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

void UAIAbilityComponent::ResetCDTimer(AMonsterCharacterBase* Monster)
{
	AIAbilityCDProperty.Value = false;
	auto FTimeScale = FMath::RandRange(3.f, 8.f);
	Monster->GetWorldTimerManager().SetTimer(AIAbilityCDProperty.Key, FTimerDelegate::CreateLambda([&]() { AIAbilityCDProperty.Value = true; }), FTimeScale, false); // 쿨타임 계산
}

void UAIAbilityComponent::AIAbilityCast(AMonsterCharacterBase* Monster, EAbilityType Type)
{
	AIAbilityCDProperty.Value = false;
	Abilities[Type]->Use(Monster);
}