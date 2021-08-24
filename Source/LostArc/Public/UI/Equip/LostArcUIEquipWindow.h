// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUIEquipWindow.generated.h"

/**
 * 
 */

enum EAccessoryType;

UCLASS()
class LOSTARC_API ULostArcUIEquipWindow : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

public:
	UPROPERTY()
	TArray<class ULostArcUIEquipSlot*> Equip_NecklaceSlot;

	UPROPERTY()
	TArray<class ULostArcUIEquipSlot*> Equip_EarringSlot;

	UPROPERTY()
	TArray<class ULostArcUIEquipSlot*> Equip_RingSlot;

	void EquipSlotConstruct(EAccessoryType Type, int32 SlotIndex);
	void EquipSlotClear(EAccessoryType Type, int32 SlotIndex);
};
