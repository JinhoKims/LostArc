// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CorpseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API UCorpseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, meta = (AllowPrivateAccess=true))
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrviateAccess = true))
	UAnimMontage* CorpseAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrviateAccess = true))
	UAnimMontage* CorpseAttackMontage;

	void PlayCorpseMontage();
	void JumpToCorpseMontageSection();
};
