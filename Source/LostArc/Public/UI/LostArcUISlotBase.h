// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Abilities/LostArcAbilityBase.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "LostArcUISlotBase.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcUISlotBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetNativeTick(bool CD);
	void SetSlotIndex(int32 Index) { SlotIndex = Index; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UImage* Image_Icon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UImage* Image_CD;

	UPROPERTY()
	class ULostArcAbilityBase* SlotData;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void SetSlotData(ULostArcAbilityBase* NewData);
	virtual void ClearSlotData();

private:
	bool bEnableTick;
	int32 SlotIndex;
};
