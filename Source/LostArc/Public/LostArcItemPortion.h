// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArcItemBase.h"
#include "LostArcItemPortion.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcItemPortion : public ULostArcItemBase
{
	GENERATED_BODY()
	
public:
	ULostArcItemPortion();
	
protected:
	virtual void Use(class ALostArcCharacter* Character) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float HealthToHeal;
};
