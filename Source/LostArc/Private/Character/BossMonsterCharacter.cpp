// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BossMonsterCharacter.h"
#include "AnimInstances/BossMonsterAnimInstance.h"
#include "Component/AIAbilityComponent.h"
#include "Controller/BossMonsterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ABossMonsterCharacter::ABossMonsterCharacter():AMonsterCharacterBase()
{
	MonsterHP = 1000.f;
	AttackRange = 500.f;
	AttackRadius = 160.f;
	
	GetCharacterMovement()->MaxWalkSpeed = 50.f; // 400.f
	GetCharacterMovement()->RotationRate = FRotator(0.f, 128.0f, 0.f);
	AIControllerClass = ABossMonsterAIController::StaticClass();
}

void ABossMonsterCharacter::PostInitializeComponents()
{
	Super::Super::PostInitializeComponents();

	MonsterAnim = Cast<UBossMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MonsterAnim != nullptr)
	{
		MonsterAnim->OnMontageEnded.AddDynamic(this, &ABossMonsterCharacter::OnAttackMontageEnded);
		MonsterAnim->OnMonsterAttackHitCheck.AddUObject(this, &ABossMonsterCharacter::MonsterAttackHitCheck);
	}
}

void ABossMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABossMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossMonsterCharacter::MonsterAttack()
{
	AbilityComponent->AIAbilityCast(this);
}

void ABossMonsterCharacter::MonsterAttack(EAbilityType Type)
{
	AbilityComponent->AIAbilityCast(this, Type);
}

void ABossMonsterCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	auto BossMonsterAnim = Cast<UBossMonsterAnimInstance>(MonsterAnim);

	for(int i = 1; i <= BossMonsterAnim->GetBasicAttackStep(); i++)
	{
		if (Montage->IsValidSectionName(FName(FString::Printf(TEXT("BasicAttack_%d"), i))))
		{
			OnAttackEnd.Broadcast();
			UAISkillBase::bAnimationRunning = false;
			AbilityComponent->ResetCDTimer(this); // 기본 공격하면 계속 초기화되니 수정 필요
			break;
		}
	}

	for (int i = 1; i <= 5; i++)
	{
		if(Montage->IsValidSectionName(FName(FString::Printf(TEXT("Skill_%d"), i))))
		{
			OnAttackEnd.Broadcast();
			UAISkillBase::bAnimationRunning = false;
			AbilityComponent->ResetCDTimer(this);
			break;
		}
	}
}
