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
	
	AbilityComponent = CreateDefaultSubobject<UAIAbilityComponent>(TEXT("ABILITY"));
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

	if(bInterrupted)
	{
		if(BossState == EBossState::Groggy)
		{
			if(AbilityComponent->GetIndicatorActorRef() != nullptr)
			{
				AbilityComponent->GetIndicatorActorRef()->Destroy();
			}
			if(Montage->IsValidSectionName(FName("Skill_2")))
			{
				if(AbilityComponent->GetMeteorActorRef() != nullptr)
				{
					AbilityComponent->GetMeteorActorRef()->Destroy();
				}
			}
		}
	}
	
	for(int i = 1; i <= BossMonsterAnim->GetBasicAttackStep(); i++)
	{
		if (Montage->IsValidSectionName(FName(FString::Printf(TEXT("BasicAttack_%d"), i))))
		{
			UAISkillBase::bMonsterAnimationRunning = false;
			break;
		}
	}

	for (int i = 1; i < 5; i++)
	{
		if(Montage->IsValidSectionName(FName(FString::Printf(TEXT("Skill_%d"), i))))
		{
			UAISkillBase::bMonsterAnimationRunning = false;
			bBossIsDisable = false;
			AbilityComponent->ResetCDTimer(this);
			GetCapsuleComponent()->SetCollisionProfileName(FName("Monster"));
			break;
		}
	}
	
	if(Montage->IsValidSectionName(FName("Groggy")))
	{
		BossState = EBossState::Default;
		AbilityComponent->ResetCDTimer(this);
		UAISkillBase::bMonsterAnimationRunning = false;
	}
}

float ABossMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FFinalDamage = Super::Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(bIsAbsent && BossState != EBossState::Groggy)
	{
		BossState = EBossState::Groggy; // 중복으로 스턴먹는거 방지
		
		MonsterAnim->Montage_Play(Cast<UBossMonsterAnimInstance>(MonsterAnim)->Boss_Groggy_Montage);
		
	}
	
	return FFinalDamage;
}


float ABossMonsterCharacter::GetBasicAttackRange()
{
	return AbilityComponent->GetBasicAttackRange();
}
