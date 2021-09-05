// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArcCharacterInterface.h"
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
class LOSTARC_API ULostArcCharacterEquipComponent : public UActorComponent, public ILostArcCharacterInterface
{
	GENERATED_BODY()

public:	
	FOnEquipSlotUpdateDelegate EquipSlotUpdate;

protected:
	virtual void InitializeComponent() override;

public:	
	ULostArcCharacterEquipComponent();
	
	void EquipMounts(class ULostArcItemEquipBase* NewEquip);
	virtual void UseAbility(int32 SlotIndex) override; // SlotIndex로 EqiupSlot 찾기(0, 1~2, 3~4)
	
	class ULostArcItemEquipBase* GetEquipItem(EAccessoryType Type, int32 SlotIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TMap<TEnumAsByte<EAccessoryType>, int32> EquipMaxSlot;
	TMap<EAccessoryType, FEquipSlot> EquipSlot;
};