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
	virtual void RefreshSlotData(class ULostArcAbilityBase* NewData);
	virtual void UnBindSlotData();
	void SetSlotIndex(int32 Index) { SlotIndex = Index; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UImage* Image_Icon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UImage* Image_CD;

	UPROPERTY()
	class ULostArcAbilityBase* SlotData;

	FDelegateHandle AbilityCDHandle;
	int32 SlotIndex;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	bool bEnableTick;
};
