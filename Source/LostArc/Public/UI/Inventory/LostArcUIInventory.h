// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUIInventory.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcUIInventory : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

public:
	UPROPERTY()
	TArray<class ULostArcUIInventorySlot*> InventorySlot;

	void InventorySlotConstruct(int32 SlotIndex);
	void UpdateItemQuantity(int32 SlotIndex);
	void InventorySlotClear(int32 SlotIndex);
};
