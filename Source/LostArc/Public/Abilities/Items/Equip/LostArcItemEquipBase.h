// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Component/LostArcInventoryComponent.h"
#include "Component/LostArcCharacterEquipComponent.h"
#include "LostArcItemEquipBase.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcItemEquipBase : public ULostArcItemBase
{
	GENERATED_BODY()
	
public:
	int32 EquipSlotIndex;
	int32 MaxEqiupSlotCount;
	EAccessoryType Type;
	
public:
	ULostArcItemEquipBase(const FObjectInitializer& ObjectInitializer);
	bool Use(ALostArcCharacter* Character) override;
	void SetEquipSlotIndex(int32 index);
	int32 GetEquipSlotIndex() { return EquipSlotIndex; }
	virtual void Dismount(ALostArcCharacter* Character);
	EAccessoryType GetType() { return Type; }


};
