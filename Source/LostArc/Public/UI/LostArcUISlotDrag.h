// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "LostArcUISlotDrag.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcUISlotDrag : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	int32 SlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> SlotType;
};
