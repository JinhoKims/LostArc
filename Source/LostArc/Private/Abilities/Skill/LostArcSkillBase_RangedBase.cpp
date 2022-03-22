// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Skill/LostArcSkillBase_RangedBase.h"
#include "Component/LostArcCharacterAbilityComponent.h"
#include "Controller/LostArcPlayerController.h"

bool ULostArcSkillBase_RangedBase::Use(ALostArcPlayerCharacter* Character)
{
	switch (Skill_State)
	{
	case EAbilityState::Stand:
		if(AbilityStateCheck(Character))
		{
			ActivityRangedCursor(true, Character);
			return false;
		}
		break;
	case EAbilityState::Focusing:
		if(AbilityStateCheck(Character))
		{
			return Super::Use(Character); // 스킬 실행
		}
		break;
	}
	
	return false;
}

void ULostArcSkillBase_RangedBase::ActivityRangedCursor(bool bUse, ALostArcPlayerCharacter* Character)
{
	auto PController = Character->GetNetOwningPlayer()->GetPlayerController(GetWorld());
	auto ArcPController = Cast<ALostArcPlayerController>(PController);
	auto AComponent = Character->AbilityComponent;
	
	if(bUse)
	{
		AComponent->ResetRangedAbilitiesState(Skill_Type); // 다른 스킬 상태 초기화
		Skill_State = EAbilityState::Focusing;
		ArcPController->ChangeCursor(Skill_Indicator); // 스킬 커서 변환
	}
	else
	{
		if(Skill_State == EAbilityState::Focusing)
		{
			Skill_State = EAbilityState::Stand;
			ArcPController->ChangeCursor(nullptr);
		}
	}
}

void ULostArcSkillBase_RangedBase::SpawnSkillActor(ALostArcPlayerCharacter* Character)
{
	// FTransform Transform;
	// Transform.SetLocation(SpawnLocation);
	//
	//
	// GetWorld()->SpawnActor<AActor>(Skill_Actor, Transform);
	//
}

void ULostArcSkillBase_RangedBase::ActorHitDetection(FVector Location, ALostArcPlayerCharacter* Character)
{
	HitLocation = Location;
	HitDetection(Character);
}

void ULostArcSkillBase_RangedBase::HitDetection(ALostArcPlayerCharacter* Character)
{
	TPair<FCollisionQueryParams, TArray<FHitResult>> HitResultProperty(FCollisionQueryParams(NAME_None, false, Character), TArray<FHitResult>());
	float dotValue = FMath::Cos(((PI * 2) / 360) * (SkillRadius.Value / 2));;
	FDamageEvent DamageEvent;
	FVector direction;
	
	GetWorld()->SweepMultiByChannel(HitResultProperty.Value, HitLocation, HitLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(SkillRadius.Key), HitResultProperty.Key);
	
	for (int32 i = 0; i < HitResultProperty.Value.Num(); i++)
	{
		FHitResult hit = HitResultProperty.Value[i];
		if (hit.Actor.IsValid())
		{
			direction = hit.Actor.Get()->GetActorLocation() - HitLocation;
			if (direction.Size() < SkillRadius.Key)
			{
				if (FVector::DotProduct(direction.GetSafeNormal(), HitLocation) > dotValue)
				{
					UE_LOG(LogTemp,Warning,TEXT("Taking Damage : %f"), Character->StatComponent->GetCurrentAttributeValue(EAttributeType::ATK) * SkillRatio);
					hit.Actor->TakeDamage(Character->StatComponent->GetCurrentAttributeValue(EAttributeType::ATK) * SkillRatio, DamageEvent, Character->GetController(), Character);
				}
			}
		}
	}
}
