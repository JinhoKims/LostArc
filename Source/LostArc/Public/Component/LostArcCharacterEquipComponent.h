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

USTRUCT(Atomic, BlueprintType)
struct FEquipSlot
{
	GENERATED_BODY()
	TArray<class ULostArcItemEquipBase*> EquipArray;
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEquipSlotUpdateDelegate, EAccessoryType, int32);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcCharacterEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FOnEquipSlotUpdateDelegate EquipSlotClear;
	FOnEquipSlotUpdateDelegate EquipSlotUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TMap<TEnumAsByte<EAccessoryType>, TSubclassOf<class ULostArcItemEquipBase>> EquipTable;

	TMap<EAccessoryType, FEquipSlot> EquipSlot;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	ULostArcCharacterEquipComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DismountEquip(class ULostArcItemEquipBase* OwnerEquip, int32 Index);
	void EquipMounts(class ULostArcItemEquipBase* NewEquip);

	class ULostArcItemEquipBase* GetEquipItem(EAccessoryType Type, int32 Index);
};