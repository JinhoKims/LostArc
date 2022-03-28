// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BossMonsterCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

ABossMonsterCharacter::ABossMonsterCharacter():AMonsterCharacterBase()
{
	MonsterHP = 1000.f;
	AttackRange = 500.f;
	AttackRadius = 160.f;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void ABossMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABossMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABossMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
