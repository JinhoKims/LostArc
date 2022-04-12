// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MonsterCharacterBase.h"
#include "AnimInstances/MonsterBaseAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Component/AIAbilityComponent.h"
#include "Controller/MonsterBaseAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMonsterCharacterBase::AMonsterCharacterBase()
{
	// MonsterHP = 100.f;
	// GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed; 
	// BasicAttackRange = 250.f;
	// GetCharacterMovement()->RotationRate = FRotator(0.f, 64.0f, 0.f);
	
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	AIControllerClass = AMonsterBaseAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMonsterCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MonsterAnim = Cast<UMonsterBaseAnimInstance>(GetMesh()->GetAnimInstance());
	if (MonsterAnim != nullptr)
	{
		MonsterAnim->OnMontageEnded.AddDynamic(this, &AMonsterCharacterBase::OnAttackMontageEnded);
	}
}

// Called when the game starts or when spawned
void AMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp,Warning,TEXT(" Rnage : %f"), BasicAttackRange);

	
	
}

float AMonsterCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UE_LOG(LogTemp,Warning,TEXT("%f"), FFinalDamage);

	if (FFinalDamage > 0.f)
	{
		MonsterHP -= FFinalDamage;
		if(MonsterHP <= 0.f)
		{
			MonsterAnim->SetDeadAnim();
			SetActorEnableCollision(false);
			GetController()->Destroyed();
		}
	}

	return FFinalDamage;
}

float AMonsterCharacterBase::GetBasicAttackRange()
{
	return BasicAttackRange;
}

void AMonsterCharacterBase::MonsterAttack()
{
	MonsterAnim->PlayAttackMontage();
}

void AMonsterCharacterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	for(int i = 1; i <= MonsterAnim->GetBasicAttackMontageSize(); i++)
	{
		if (Montage->IsValidSectionName(FName(FString::Printf(TEXT("Attack_%d"), i))))
		{
			OnBasicAttackEnd.Broadcast();
			break;
		}
	}
}