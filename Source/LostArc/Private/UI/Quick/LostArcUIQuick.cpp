// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Quick/LostArcUIQuick.h"
#include "UI/Quick/LostArcUIQuickSlot.h"

void ULostArcUIQuick::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 16; i++)
	{
		QuickSlot.Add(Cast<ULostArcUIQuickSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_QuickSlot_%d"), i)))));
	}
}
