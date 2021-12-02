// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUITabs.generated.h"

UENUM(BlueprintType)
enum ETabType
{
	InvenTab UMETA(DisplayName = "InvenTab"),
	EquipTab UMETA(DisplayName = "EquipTab")
};

UCLASS()
class LOSTARC_API ULostArcUITabs : public UUserWidget
{
	GENERATED_BODY()

public:
	TEnumAsByte<ETabType> TabType;
	void SetUITabsFromParent(UUserWidget* Parent, ETabType ParType);

private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override; 
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	UPROPERTY()
	UUserWidget* ParentWidget;
};
