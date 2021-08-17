// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LostArcPotionHealth.h"

ULostArcPotionHealth::ULostArcPotionHealth(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ItemName = FString("Potion_Health");
}

bool ULostArcPotionHealth::Use(ALostArcCharacter* Character)
{
	return false;
}
