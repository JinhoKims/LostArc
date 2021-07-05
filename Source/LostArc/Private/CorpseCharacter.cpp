// Fill out your copyright notice in the Description page of Project Settings.


#include "CorpseCharacter.h"
#include "CorpseAnimInstance.h"
#include "CorpseAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACorpseCharacter::ACorpseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	MonsterHP = 50.0f;

	AIControllerClass = ACorpseAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

// Called when the game starts or when spawned
void ACorpseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACorpseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACorpseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Corpseanim = Cast<UCorpseAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called to bind functionality to input
void ACorpseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACorpseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FInalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (FInalDamage > 0.f)
	{
		MonsterHP -= FInalDamage;
		UE_LOG(LogTemp, Warning, TEXT("Current HP : %f"), MonsterHP);
		if (MonsterHP <= 0.f)
		{
			Corpseanim->JumpToCorpseMontageSection();
		}
		else
		{
			Corpseanim->PlayCorpseMontage();
		}
	}
	return FInalDamage;
}

void ACorpseCharacter::Attack()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, PlayerCharacter->GetActorLocation());
}

