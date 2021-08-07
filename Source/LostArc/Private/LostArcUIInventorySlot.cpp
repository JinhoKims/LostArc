// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArcUIInventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULostArcUIInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemText")));
}