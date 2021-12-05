// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "LostArcItemEquip_Necklace.generated.h"

UCLASS()
class LOSTARC_API ULostArcItemEquip_Necklace : public ULostArcItemEquipBase
{
	GENERATED_BODY()
	
public:
	ULostArcItemEquip_Necklace(const FObjectInitializer& ObjectInitializer);
	virtual bool Use(ALostArcCharacter* Character) override;
	virtual void Equipment(ALostArcCharacter* Character) override;
	virtual void Dismount(ALostArcCharacter* Character) override;
};
