// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcAnimInstance.h"

UArcAnimInstance::UArcAnimInstance() :Super() {}

void UArcAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UArcAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UArcAnimInstance::PlayAttackMontage()
{
	Montage_Play(auto_AttackMontage, 1.0f);
}

void UArcAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UArcAnimInstance::AnimNotify_AttackHitCheck()
{
}

void UArcAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	//check(Montage_IsPlaying(auto_AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), auto_AttackMontage);
}

FName UArcAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	check(FMath::IsWithinInclusive<int32>(Section, 1, 3));
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}


