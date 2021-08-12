// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterAbilityEvade.h"
#include "Character/LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Components/CapsuleComponent.h"

void ULostArcCharacterAbilityEvade::ConstructAbility(float mana, float cooldown, float factor)
{
	Super::ConstructAbility(mana, cooldown, factor);
}

void ULostArcCharacterAbilityEvade::Use(ALostArcCharacter* Character)
{
	Super::Use(Character);
	
	if (bAbilityNowAvailable)
	{
		auto Anim = Character->AnimInstance;

		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
		Anim->Montage_Play(Anim->Evade_Montage, 1.f); // Montage_Play()가 시작되면 이전에 실행 중이던 몽타주는 자동으로 End된다. 
	}
}

bool ULostArcCharacterAbilityEvade::AbilityStatusCheck(ALostArcCharacter* Character)
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
	return true;
}
