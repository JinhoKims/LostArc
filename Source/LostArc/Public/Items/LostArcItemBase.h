// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LostArcItemBase.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	ULostArcItemBase();
	virtual void Use(class ALostArcCharacter* Character) PURE_VIRTUAL(ULostArcItemBase, );

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	UPROPERTY()
	class ULostArcInventoryComponent* OwningInventory;
};
