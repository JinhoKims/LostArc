// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/LostArcCharacterInterface.h"
#include "LostArcInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInvenSlotUpdateDelegate, int32)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcInventoryComponent : public UActorComponent, public ILostArcCharacterInterface
{
	GENERATED_BODY()
	
public:
	FOnInvenSlotUpdateDelegate InvenSlotUpdate;

	ULostArcInventoryComponent();
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UseAbility(int32 SlotIndex) override;
	virtual void SwappingSlot(int32 OwnerIndex, int32 DistIndex) override;

	void UseItem(int32 SlotInex);	
	void AddPickupItem(FString ItemName, int32 ItemCount = 1);
	void MoveItem(class ULostArcItemBase* OwnerItem, int32 distIndex = -1);
	void SwapSlot(int32 ownerIndex, int32 distIndex);

	bool ConsumableCheck(class ULostArcItemBase* NewItem, int32 ItemCount);
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