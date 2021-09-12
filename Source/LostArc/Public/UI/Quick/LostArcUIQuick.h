// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUIQuick.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcUIQuick : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<class ULostArcUISlotBase*> QuickSlot;
};
