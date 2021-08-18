// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LostArcInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARC_API ULostArcInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULostArcInventoryComponent();
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddPickupItem(FString ItemName, int32 ItemCount = 1);
	bool ConsumableItemCheck(class ULostArcItemBase* NewItem, int32 ItemCount);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<ULostArcItemBase>> ItemClass;

	TMap<FString, TSubclassOf<ULostArcItemBase>> ItemTable;

	TArray<class ULostArcItemBase*> InventorySlot;
};