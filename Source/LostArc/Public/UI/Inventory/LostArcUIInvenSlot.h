// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LostArcUISlotBase.h"
#include "LostArcUIInvenSlot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcUIInvenSlot : public ULostArcUISlotBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void SetNativeTick(bool CD) override;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UImage* Image_BG;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* Text_Quantity;
};

