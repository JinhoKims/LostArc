// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "LostArcItemEquipBase.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcItemEquipBase : public ULostArcItemBase
{
	GENERATED_BODY()
	
public:
	ULostArcItemEquipBase(const FObjectInitializer& ObjectInitializer);
	bool Use(ALostArcCharacter* Character) override;
};
