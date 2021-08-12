// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterAbilityBase.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

bool ULostArcCharacterAbilityBase::bAnimationRunning = false;

void ULostArcCharacterAbilityBase::ConstructAbility(float mana, float cooldown, float factor)
{
	ManaCost = mana;
	CoolDown = cooldown;
	Damage_Factor = factor;
	bAbilityNowCD = false;
}

void ULostArcCharacterAbilityBase::Use(ALostArcCharacter* Character)
{
	bAbilityNowAvailable = AbilityStatusCheck(Character);

	if (bAbilityNowAvailable)
	{
		CharacterRotatetoCursor(Character);
		Character->GetWorldTimerManager().SetTimer(AbilityCoolDownTimer, FTimerDelegate::CreateLambda([=]() {bAbilityNowCD = false; OnAbilityhasCD.Broadcast(false); }), CoolDown, false);
		Character->StatComponent->SetCurrentAttributeValue(EAttributeType::MP, Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::MP) - ManaCost);
		bAbilityNowCD = true;
		bAnimationRunning = true;
		OnAbilityhasCD.Broadcast(true);
	}
}

void ULostArcCharacterAbilityBase::HitCheck(ALostArcCharacter* Character)
{
	FDamageEvent DamageEvent;

	for (int32 i = 0; i < HitResultProperty.Value.Num(); i++)
	{
		FHitResult hit = HitResultProperty.Value[i];
		if (hit.Actor.IsValid())
		{
			hit.Actor->TakeDamage(Character->StatComponent->GetCurrnetAttributeValue(EAttributeType::ATK) * Damage_Factor, DamageEvent, Character->GetController(), Character);
		}
	}
}

bool ULostArcCharacterAbilityBase::AbilityStatusCheck(ALostArcCharacter* Character)
{
	if (bAbilityNowCD)
	{
		UE_LOG(LogTemp, Warning, TEXT("CoolDown Left is : %f"), Character->GetWorldTimerManager().GetTimerRemaining(AbilityCoolDownTimer));
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

void ULostArcCharacterAbilityBase::CharacterRotatetoCursor(ALostArcCharacter* Character)
{
	FHitResult Hit;
	Cast<APlayerController>(Character->GetController())->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	float ang = FMath::Atan2(Hit.ImpactPoint.Y - Character->GetActorLocation().Y, Hit.ImpactPoint.X - Character->GetActorLocation().X) * 180 / PI;
	if (ang < 0) ang += 360;
	
	Character->SetActorRelativeRotation(FRotator(0.0f, ang, 0.0f));
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Character->GetController(), Character);
}

