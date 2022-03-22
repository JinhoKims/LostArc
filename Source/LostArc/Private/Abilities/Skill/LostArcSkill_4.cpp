// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Skill/LostArcSkill_4.h"
#include "PhysXInterfaceWrapperCore.h"
#include "Components/CapsuleComponent.h"

ULostArcSkill_4::ULostArcSkill_4(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 8.f;
	ManaCost = 20.f;
	SkillRatio = 2.f;
	SkillRadius.Key = 600.f;
	SkillRadius.Value = 360.f;
	Skill_Type = EAbilityType::MeleeSkill_4;
	Name = "Skill_4";

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Earth(TEXT("Blueprint'/Game/Luos8Elements/Blueprints/Earth/BP_Earth_Def_01_Life.BP_Earth_Def_01_Life'"));
	if (BP_Earth.Object)
	{
		SpawnActor = (UClass*)BP_Earth.Object->GeneratedClass;
	}
}

bool ULostArcSkill_4::Use(ALostArcPlayerCharacter* Character)
{
	if (Super::Use(Character))
	{
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_4_Montage, 1.f);
		return true;
	}
	else
		return false;
}

void ULostArcSkill_4::HitDetection(ALostArcPlayerCharacter* Character)
{
	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
	
	auto SpawnLocation = FVector(Character->GetActorTransform().GetLocation().X, Character->GetActorTransform().GetLocation().Y, Character->GetActorTransform().GetLocation().Z - 70);
	FTransform Transform;
	Transform.SetLocation(SpawnLocation);
	Transform.SetRotation(Character->GetActorTransform().GetRotation());
	
	GetWorld()->SpawnActor<AActor>(SpawnActor, Transform);
	
	Super::HitDetection(Character);
}