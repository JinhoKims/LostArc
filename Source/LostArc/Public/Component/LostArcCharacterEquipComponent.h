// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArcCharacterInterface.h"
#include "LostArcInventoryComponent.h"
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

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipSlotUpdateDelegate, int32);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcCharacterEquipComponent : public UActorComponent, public ILostArcCharacterInterface
{
	GENERATED_BODY()
	
public:	
	FOnEquipSlotUpdateDelegate EquipSlotUpdate;
	
public:	
	ULostArcCharacterEquipComponent();
	virtual void UseAbility(int32 SlotIndex) override;
	virtual void SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent) override;
	virtual bool SetAbility(ULostArcAbilityBase* OwnerAbility, int32 SlotIndex = -1) override;
	virtual ULostArcAbilityBase* GetAbility(int32 SlotIndex, bool bTrans = false) override;
	
	int32 IndexEncoding(EAccessoryType AcType, int32 Index);
	EAccessoryType IndexDecoding(int32 &SlotIndex, bool bTrans = true);
	
protected:
	virtual void InitializeComponent() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TMap<TEnumAsByte<EAccessoryType>, int32> EquipMaxSlot;
	TMap<EAccessoryType, FEquipSlot> EquipSlot;

	ILostArcCharacterInterface* Interface;
};