// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterAbilityComponent.h"
#include "Controller/LostArcPlayerController.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcCharacterStatComponent.h"
#include "Abilities/LostArcAbilityBase.h"
#include "Abilities/Skill/LostArcSkillBase.h"
#include "Abilities/Skill/LostArcSkill_BasicAttack.h"
#include "Abilities/Skill/LostArcSkill_1.h"
#include "Abilities/Skill/LostArcSkill_2.h"
#include "Abilities/Skill/LostArcSkill_3.h"
#include "Abilities/Skill/LostArcSkill_4.h"
#include "Abilities/Skill/LostArcSkill_Dodge.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
ULostArcCharacterAbilityComponent::ULostArcCharacterAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	
	AbilityClass.Init(ULostArcSkillBase::StaticClass(), 10);
}

void ULostArcCharacterAbilityComponent::InitializeComponent() // Init 컴포넌트는 컴파일 타임에 생성자가 호출된 후에 같이 호출되는 경향이 있기에 미리 AbilityClass를 초기화해줘야한다.
{
	Super::InitializeComponent();

	for (int i = 0; i < 10; i++)
	{
		Abilities.Add(NewObject<ULostArcSkillBase>(this, AbilityClass[i].Get())); // Get()은 UClass 원본 데이터(파생형)를 반환한다.
	}
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
	ULostArcSkillBase::bAnimationRunning = false;
	Abilities.Empty();
}

void ULostArcCharacterAbilityComponent::AbilityCast(EAbilityType Type)
{
	Abilities[Type]->Use(Cast<ALostArcCharacter>(GetOwner()));
}

void ULostArcCharacterAbilityComponent::AbilityHitDetection(EAbilityType Type)
{
	Abilities[Type]->HitDetection(Cast<ALostArcCharacter>(GetOwner()));
}

ULostArcSkillBase* ULostArcCharacterAbilityComponent::GetAbilites(EAbilityType Type)
{
	return Abilities[Type];
}

void ULostArcCharacterAbilityComponent::AbilityMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) // Evade
	{
		if (Montage->IsValidSectionName(TEXT("BasicAttack_1")))
		{
			Cast<ULostArcSkill_BasicAttack>(GetAbilites(EAbilityType::BasicAttack))->SetBasicAttacking(false);
			Cast<ULostArcSkill_BasicAttack>(GetAbilites(EAbilityType::BasicAttack))->BasicAttackEndComboState();
		}
		return;
	}

	if (Montage->IsValidSectionName(TEXT("BasicAttack_1")))
	{
		Cast<ULostArcSkill_BasicAttack>(GetAbilites(EAbilityType::BasicAttack))->SetBasicAttacking(false);
		Cast<ULostArcSkill_BasicAttack>(GetAbilites(EAbilityType::BasicAttack))->BasicAttackEndComboState();
	}

	if (Montage->IsValidSectionName(TEXT("Evade")))
	{
		Cast<ALostArcCharacter>(GetOwner())->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
		ULostArcSkillBase::bAnimationRunning = false;
	}

	for (int i = 1; i < 5; i++)
	{
		Montage->IsValidSectionName(FName(FString::Printf(TEXT("MeleeSkill_%d"), i)));
		ULostArcSkillBase::bAnimationRunning = false;
	}
}