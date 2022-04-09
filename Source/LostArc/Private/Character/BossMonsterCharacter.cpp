// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BossMonsterCharacter.h"
#include "AnimInstances/BossMonsterAnimInstance.h"
#include "Component/AIAbilityComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controller/BossMonsterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ABossMonsterCharacter::ABossMonsterCharacter():AMonsterCharacterBase()
{
	MonsterHP = 1000.f;
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 400.f
	GetCharacterMovement()->RotationRate = FRotator(0.f, 128.0f, 0.f);
	AIControllerClass = ABossMonsterAIController::StaticClass();
	IndicatorClass.Init(NULL, 4);
}

void ABossMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABossMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABossMonsterCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	auto BossMonsterAnim = Cast<UBossMonsterAnimInstance>(MonsterAnim);

	for(int i = 1; i <= BossMonsterAnim->GetBasicAttackStep(); i++)
	{
		if (Montage->IsValidSectionName(FName(FString::Printf(TEXT("BasicAttack_%d"), i))))
		{
			UAISkillBase::bAnimationRunning = false;
			break;
		}
	}

	for (int i = 1; i < 5; i++)
	{
		if(Montage->IsValidSectionName(FName(FString::Printf(TEXT("Skill_%d"), i))))
		{
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
			UAISkillBase::bAnimationRunning = false;
			AbilityComponent->ResetCDTimer(this);
			break;
		}
	}
}