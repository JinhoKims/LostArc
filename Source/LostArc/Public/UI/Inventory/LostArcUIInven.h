// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "LostArcUIInven.generated.h"

UCLASS()
class LOSTARC_API ULostArcUIInven : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshSlot(int32 Index);
	void EnableInventory();
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;
	
private:
	UPROPERTY()
	TArray<class ULostArcUISlotBase*> InvenSlot;

	class ALostArcCharacter* OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class UHorizontalBox* Horizontal_Box;
	
	bool bEnable = false;
};
