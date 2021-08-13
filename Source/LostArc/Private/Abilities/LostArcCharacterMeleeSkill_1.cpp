// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterMeleeSkill_1.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "DrawDebugHelpers.h"

void ULostArcCharacterMeleeSkill_1::ConstructAbility(float mana, float cooldown, float factor)
{
	Super::ConstructAbility(mana, cooldown, factor);
}

void ULostArcCharacterMeleeSkill_1::Use(ALostArcCharacter* Character)
{
	Super::Use(Character);

	if (bAbilityNowAvailable)
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerMeleeSkill_1_Montage, 1.f);
	}
}

void ULostArcCharacterMeleeSkill_1::HitCheck(ALostArcCharacter* Character)
{
	HitResultProperty = TPairInitializer<FCollisionQueryParams, TArray<FHitResult>>(FCollisionQueryParams(NAME_None, false, Character), TArray<FHitResult>());

	GetWorld()->SweepMultiByChannel(HitResultProperty.Value, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(300.f), HitResultProperty.Key);
	//DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 300.f, 32, FColor::Cyan, false, 1.f);
	
	Super::HitCheck(Character);
}

void ULostArcCharacterMeleeSkill_1::TestDrawArc(ALostArcCharacter* Character)
{
	FDamageEvent DamageEvent;
	float distance = 300.0f; // 부채꼴 길이
	float angleRange = 120.0f; // 부채꼴 각도
	float dotValue = FMath::Cos(((PI * 2) / 360) * (angleRange / 2));; // 부채꼴 빗변(경계)의 코사인 값 (부채꼴을 반으로 나눠 밑변을 확보한다.)
	FVector direction; // 타겟의 좌표

	for (int32 i = 0; i < HitResultProperty.Value.Num(); i++)
	{
		FHitResult hit = HitResultProperty.Value[i];
		if (hit.Actor.IsValid())
		{
			direction = hit.Actor.Get()->GetActorLocation() - Character->GetActorLocation(); // 타겟과의 거리 계산

			if (direction.Size() < distance) // 타겟과의 거리가 부채꼴 전체 길이보다 짧으면
			{
				if (FVector::DotProduct(direction.GetSafeNormal(), Character->GetActorForwardVector()) > dotValue) // 타겟과 부채꼴 중앙선(밑변)의 코사인 값이 부채꼴 빗변의 코사인 값보다 크면 (= 부채꼴 영역안에 위치함)
				{
					hit.Actor->TakeDamage(Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::ATK) * Damage_Factor, DamageEvent, Character->GetController(), Character);
				}
			}
		}
	}
	
}