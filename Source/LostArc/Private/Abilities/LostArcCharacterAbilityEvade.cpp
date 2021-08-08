// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterAbilityEvade.h"
#include "LostArcCharacter.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Components/CapsuleComponent.h"

void ULostArcCharacterAbilityEvade::ConstructAbility(float mana, float cooldown, float ratio)
{
	Super::ConstructAbility(mana, cooldown, ratio);
}


void ULostArcCharacterAbilityEvade::Use(ALostArcCharacter* Character)
{
	auto Anim = Character->AnimInstance;

	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));
	Anim->Montage_Play(Anim->Evade_Montage, 1.f); // Montage_Play()가 시작되면 이전에 실행 중이던 몽타주는 자동으로 End된다. 
}
