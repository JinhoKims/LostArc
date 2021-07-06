// Fill out your copyright notice in the Description page of Project Settings.


#include "CorpseAnimInstance.h"
#include "CorpseCharacter.h"

void UCorpseAnimInstance::PlayCorpseMontage()
{
	Montage_Play(CorpseFlinchMontage, 1.f);
}

void UCorpseAnimInstance::PlayDeathMontage()
{
	Montage_Play(CorpseDeathMontage, 1.1f);
	TryGetPawnOwner()->SetActorEnableCollision(false);
	TryGetPawnOwner()->SetLifeSpan(2.35f);
	TryGetPawnOwner()->GetController()->AController::Destroy();
}

void UCorpseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCorpseAnimInstance::PlayAttackMontage()
{
	Montage_Play(CorpseAttackMontage, 1.f);
}

void UCorpseAnimInstance::AnimNotify_CorpseAttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
