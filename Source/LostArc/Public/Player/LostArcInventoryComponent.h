// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/LostArcTypes.h"
#include "LostArcInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARC_API ULostArcInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULostArcInventoryComponent();
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddPickupItem(class ULostArcItemBase** NewItem, int32 ItemCount = 1);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<ULostArcItemBase>> ItemClass;

	UPROPERTY(meta = (AllowPrivateAccess = true))
	TMap<FString, class ULostArcItemBase*> DataTable;

	UPROPERTY(meta = (AllowPrivateAccess = true))
	TMap<class ULostArcItemBase*, FLostArcItemData> InventoryData;

	TArray<class ULostArcItemBase*> InventorySlot;

	class ULostArcItemBase* EquipmentItemGenerator();
};
