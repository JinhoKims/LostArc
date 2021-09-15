// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LostArcUISlotBase.h"
#include "LostArcUIQuickSlot.generated.h"

UCLASS()
class LOSTARC_API ULostArcUIQuickSlot : public ULostArcUISlotBase
{
	GENERATED_BODY()

public:
	void SetSlot(ULostArcUISlotBase* Owner);

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UImage* Image_Tri;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* Text_Key;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = true))
	FText KeyName;

	ULostArcUISlotBase* OwnerSlot;
};
