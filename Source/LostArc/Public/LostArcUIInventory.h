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

public:
	UPROPERTY()
	TArray<class ULostArcUIInventorySlot*> InventorySlots;
};
