// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LostArcInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInvenSlotUpdateDelegate, int32, bool)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	FOnInvenSlotUpdateDelegate InvenSlotUpdate;

	ULostArcInventoryComponent();
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ItemUse(int32 SlotInex);	

	void AddPickupItem(FString ItemName, int32 ItemCount = 1);
	void MoveItem(class ULostArcItemBase* Item, int32 ItemCount = 1);
	bool ConsumableItemCheck(class ULostArcItemBase* NewItem, int32 ItemCount);
	class ULostArcItemBase* GetSlotItem(int32 Index);
	void InventorySlotChangeNullptr(int32 Index);

	class ULostArcAbilityBase* GetSlotData(int32 Index);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<class ULostArcItemBase>> ItemClass;

	TMap<FString, TSubclassOf<class ULostArcItemBase>> ItemTable;

	TArray<class ULostArcItemBase*> InventorySlot;
};