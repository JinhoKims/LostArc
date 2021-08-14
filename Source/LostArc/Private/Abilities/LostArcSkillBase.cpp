// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcSkillBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

bool ULostArcSkillBase::bAnimationRunning = false;

bool ULostArcSkillBase::Use(ALostArcCharacter* Character)
{
	if (AbilityStateCheck(Character))
	{
		PreCast(Character);
		return true;
	}
	else
		return false;
}

bool ULostArcSkillBase::AbilityStateCheck(ALostArcCharacter* Character)
{
	if (Character->GetWorldTimerManager().IsTimerActive(AbilityCDProperty.Key))
	{
		UE_LOG(LogTemp, Warning, TEXT("CoolDown Left is : %f"), Character->GetWorldTimerManager().GetTimerRemaining(AbilityCDProperty.Key));
		return false;
	}
	if (Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::MP) < ManaCost)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Mana is : %f"), Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::MP));
		return false;
	}
	if (bAnimationRunning)
	{
		return false;
	}
	return true;
}

void ULostArcSkillBase::CharacterRotatetoCursor(ALostArcCharacter* Character)
{
	FHitResult Hit;
	Cast<APlayerController>(Character->GetController())->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	float ang = FMath::Atan2(Hit.ImpactPoint.Y - Character->GetActorLocation().Y, Hit.ImpactPoint.X - Character->GetActorLocation().X) * 180 / PI;
	if (ang < 0) ang += 360;

	Character->SetActorRelativeRotation(FRotator(0.0f, ang, 0.0f));
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Character->GetController(), Character);
}

void ULostArcSkillBase::HitDetection(ALostArcCharacter* Character)
{
	TPair<FCollisionQueryParams, TArray<FHitResult>> HitResultProperty(FCollisionQueryParams(NAME_None, false, Character), TArray<FHitResult>());
	float dotValue = FMath::Cos(((PI * 2) / 360) * (SkillRadius.Value / 2));;
	FDamageEvent DamageEvent;
	FVector direction;
	
	GetWorld()->SweepMultiByChannel(HitResultProperty.Value, Character->GetActorLocation(), Character->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(SkillRadius.Key), HitResultProperty.Key);

	for (int32 i = 0; i < HitResultProperty.Value.Num(); i++)
	{
		FHitResult hit = HitResultProperty.Value[i];
		if (hit.Actor.IsValid())
		{
			direction = hit.Actor.Get()->GetActorLocation() - Character->GetActorLocation();
			if (direction.Size() < SkillRadius.Key) // 타겟과의 거리가 부채꼴 전체 길이보다 짧으면
			{
				if (FVector::DotProduct(direction.GetSafeNormal(), Character->GetActorForwardVector()) > dotValue) // 타겟과 부채꼴 중앙선(밑변)의 코사인 값이 부채꼴 빗변의 코사인 값보다 크면 (= 부채꼴 영역안에 위치함)
				{
					hit.Actor->TakeDamage(Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::ATK) * SkillRatio, DamageEvent, Character->GetController(), Character);
				}
			}
		}
	}
}

void ULostArcSkillBase::PreCast(ALostArcCharacter* Character)
{
	CharacterRotatetoCursor(Character);
	Character->GetWorldTimerManager().SetTimer(AbilityCDProperty.Key, FTimerDelegate::CreateLambda([=]() {AbilityCDProperty.Value.Broadcast(false); }), CoolDown, false);
	Character->StatComponent->SetCurrentAttributeValue(EAttributeType::MP, Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::MP) - ManaCost);
	bAnimationRunning = true;
	AbilityCDProperty.Value.Broadcast(true);
}