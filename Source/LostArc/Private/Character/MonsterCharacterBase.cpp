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
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	AIControllerClass = AMonsterBaseAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	AbilityComponent = CreateDefaultSubobject<UAIAbilityComponent>(TEXT("ABILITY"));
}

void AMonsterCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MonsterAnim = Cast<UMonsterBaseAnimInstance>(GetMesh()->GetAnimInstance());
	if (MonsterAnim != nullptr)
	{
		MonsterAnim->OnMontageEnded.AddDynamic(this, &AMonsterCharacterBase::OnAttackMontageEnded);
		MonsterAnim->OnMonsterAttackHitCheck.AddUObject(AbilityComponent, &UAIAbilityComponent::AIAbilityHitDetection);
	}
}

// Called when the game starts or when spawned
void AMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

float AMonsterCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UE_LOG(LogTemp,Warning,TEXT("%f"), FFinalDamage);
	
	return FFinalDamage;
}

float AMonsterCharacterBase::GetBasicAttackRange()
{
	return AbilityComponent->GetBasicAttackRange();
}

void AMonsterCharacterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	
}
