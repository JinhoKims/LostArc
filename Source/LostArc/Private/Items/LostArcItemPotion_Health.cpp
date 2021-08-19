// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/LostArcItemPotion_Health.h"

ULostArcItemPotion_Health::ULostArcItemPotion_Health(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ItemName = FString("Potion_Health");

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Item/battle_item_01_7.battle_item_01_7'"));
	if (T2D_ICON.Object != NULL)
	{
		ItemTexture2D = T2D_ICON.Object;
	}
}