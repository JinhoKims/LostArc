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
	UTexture2D* BgTexture2D;
	UTexture2D* ItemTexture2D;
	
	FOnItemQuantityUpdateDelegate ItemQuantityUpdate;
	
public:
	/** Returns if the item is consumable (MaxCount <= 0)*/
	bool IsConsumable() const;

	EItemType GetItemType() const;
	int32 GetMaxCount() { return MaxCount; }
	FString GetItemName() { return Name; }
	int32 GetItemQuantity() { return ItemQuantity; }
	UTexture2D* GetItemTexture2D() { return ItemTexture2D; }
	UTexture2D* GetBgTexture2D() { return BgTexture2D; }
	int32 GetInventorySlotIndex() { return InventorySlotIndex; }
	void SetInventorySlotIndex(int32 index);

	virtual bool Use(ALostArcCharacter* Character) override;
	virtual bool AbilityStateCheck(ALostArcCharacter* Character) override;
	void AddItemCount(int32 Count);


protected:
	int32 MaxCount;
	int32 ItemQuantity;
	EItemType ItemType;
	int32 InventorySlotIndex;
};
