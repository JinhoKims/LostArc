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
	FString ItemName;
	EItemType ItemType;
	UTexture2D* ItemTexture2D;
	int32 ItemQuantity;
	
public:
	/** Returns if the item is consumable (MaxCount <= 0)*/
	bool IsConsumable() const;
	EItemType GetItemType() const;
	int32 GetMaxCount() { return MaxCount; }
	FString GetItemName() { return ItemName; }
	int32 GetItemQuantity() { return ItemQuantity; }

	virtual bool Use(ALostArcCharacter* Character) override;
	virtual bool AbilityStateCheck(ALostArcCharacter* Character) override;
	void AddItemCount(int32 Count);

protected:
	virtual void PreCast(ALostArcCharacter* Character);
};
