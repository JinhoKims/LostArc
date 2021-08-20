// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Items/LostArcItemPotionBase.h"
#include "LostArcItemPotion_Health.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcItemPotion_Health : public ULostArcItemPotionBase
{
	GENERATED_BODY()
	
public:
	ULostArcItemPotion_Health(const FObjectInitializer& ObjectInitializer);

	virtual bool Use(ALostArcCharacter* Character) override;

private:
	float Value = 100.f;
};
