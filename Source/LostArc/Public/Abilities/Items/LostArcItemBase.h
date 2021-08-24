// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcAbilityBase.h"
#include "LostArcItemBase.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnItemQuantityUpdateDelegate);

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
	int32 MaxCount;
	FString ItemName;
	EItemType ItemType;
	UTexture2D* BgTexture2D;
	UTexture2D* ItemTexture2D;
	int32 ItemQuantity;
	int32 InventorySlotIndex;
	FOnItemQuantityUpdateDelegate ItemQuantityUpdate;
	
public:
	/** Returns if the item is consumable (MaxCount <= 0)*/
	bool IsConsumable() const;
	EItemType GetItemType() const;
	int32 GetMaxCount() { return MaxCount; }
	FString GetItemName() { return ItemName; }
	int32 GetItemQuantity() { return ItemQuantity; }
	UTexture2D* GetItemTexture2D() { return ItemTexture2D; }
	UTexture2D* GetBgTexture2D() { return BgTexture2D; }
	void SetInventorySlotIndex(int32 index);
	int32 GetInventorySlotIndex() { return InventorySlotIndex; }

	virtual bool Use(ALostArcCharacter* Character) override;
	virtual bool AbilityStateCheck(ALostArcCharacter* Character) override;
	void AddItemCount(int32 Count);

protected:
	virtual void PreCast(ALostArcCharacter* Character);


};
