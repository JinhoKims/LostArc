// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "LostArcUISlotDrag.generated.h"

UENUM(BlueprintType)
enum ESlotType
{
	Inven UMETA(DisplayName = "Inven"),
	Equip UMETA(DisplayName = "Equip"),
	Quick UMETA(DisplayName = "Quick")
};

UCLASS()
class LOSTARC_API ULostArcUISlotDrag : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	TEnumAsByte<ESlotType> SlotType;
	UActorComponent* SlotComponent;
	int32 SlotIndex;
};
