// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LostArcCharacterEquipComponent.generated.h"

UENUM(BlueprintType)
enum EAccessoryType
{
	Necklace UMETA(DisplayName = "Necklace"),
	Earring UMETA(DisplayName = "Earring"),
	Ring UMETA(DisplayName = "Ring")
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEquipSlotUpdateDelegate, EAccessoryType, int32);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcCharacterEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FOnEquipSlotUpdateDelegate EquipSlotUpdate;
	FOnEquipSlotUpdateDelegate EquipSlotClear;

	TArray<class ULostArcItemEquipBase*> NecklaceSlot;
	TArray<class ULostArcItemEquipBase*> EarringSlot;
	TArray<class ULostArcItemEquipBase*> RingSlot;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	ULostArcCharacterEquipComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool EquipmentMounts(class ULostArcItemEquipBase* NewEquip, EAccessoryType Type);
	class ULostArcItemEquipBase* GetEquipItem(EAccessoryType Type, int32 Index);
	void DismountEquip(EAccessoryType Type, int32 Index);
};