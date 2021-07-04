// Fill out your copyright notice in the Description page of Project Settings.


#include "CorpseAnimInstance.h"
#include "CorpseCharacter.h"

void UCorpseAnimInstance::PlayCorpseMontage()
{
	Montage_Play(CorpseAnimMontage, 1.f);
}

void UCorpseAnimInstance::JumpToCorpseMontageSection()
{
	
}