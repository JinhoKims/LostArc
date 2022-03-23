// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Skill/LostArcSkill_5.h"
#include "Component/LostArcCharacterAbilityComponent.h"

ULostArcSkill_5::ULostArcSkill_5(const FObjectInitializer& ObjectInitializer)
{
	CoolDown = 5.f;
	ManaCost = 30.f;
	SkillRatio = 0.3f;
	SkillRadius.Key = 350.f;
	SkillRadius.Value = 360.f;
	Skill_Type = EAbilityType::RangedSpell_1;
	Name = "Skill_5";
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_ICE_ATK(TEXT("Blueprint'/Game/UI/Ability/RangedSkill/Ranged_1/BP_Ranged_Ice_Atk.BP_Ranged_Ice_Atk'"));
	if (BP_ICE_ATK.Object)
	{
		Skill_Actor = (UClass*)BP_ICE_ATK.Object->GeneratedClass;
		
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Indicator(TEXT("Blueprint'/Game/UI/Ability/RangedSkill/Ranged_1/BP_RangedSkill_Indicator_1.BP_RangedSkill_Indicator_1'"));
	if (BP_Indicator.Object)
	{
		Skill_Indicator = (UClass*)BP_Indicator.Object->GeneratedClass;
	}
}

bool ULostArcSkill_5::Use(ALostArcPlayerCharacter* Character)
{
	if(Super::Use(Character))
	{
		FHitResult TraceHitResult;
		auto PController = Character->GetNetOwningPlayer()->GetPlayerController(GetWorld());
		PController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		HitLocation = TraceHitResult.Location;
		
		SpawnLocation = FVector(TraceHitResult.Location.X, TraceHitResult.Location.Y, TraceHitResult.Location.Z + 1000.f);

		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerRangedSkill_1_Montage, 1.f);
		return true;
	}

	return false;
}

void ULostArcSkill_5::Spawn_SkillActor(ALostArcPlayerCharacter* Character)
{
	FTransform Transform;
	Transform.SetLocation(SpawnLocation);
	GetWorld()->SpawnActor<AActor>(Skill_Actor, Transform);
}
