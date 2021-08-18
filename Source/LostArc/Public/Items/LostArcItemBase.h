// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcAbilityBase.h"
#include "LostArcItemBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EItemType
{
	ITEM_Equip UMETA(DisplayName = "Equip"),
	ITEM_Potion UMETA(DisplayName = "Potion"),
	ITEM_None  UMETA(DisplayName = "None")
};

UCLASS()
class LOSTARC_API ULostArcItemBase : public ULostArcAbilityBase
{
	GENERATED_BODY()
	
public:
	/** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
	int32 MaxCount;
	/** User-visible short name */
	FString ItemName;
	/** Type of this item, set in native parent class */
	EItemType ItemType;

public:
	/** Returns if the item is consumable (MaxCount <= 0)*/
	bool IsConsumable() const;

	EItemType GetItemType() const;

	int32 GetMaxCount() { return MaxCount; }
};
