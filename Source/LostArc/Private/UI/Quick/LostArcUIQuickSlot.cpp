// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Quick/LostArcUIQuickSlot.h"

void ULostArcUIQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	SlotType = ESlotType::Quick;
	Text_Key->SetText(KeyName);
}

