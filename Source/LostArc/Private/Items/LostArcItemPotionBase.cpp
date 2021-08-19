// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LostArcItemPotionBase.h"


ULostArcItemPotionBase::ULostArcItemPotionBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ItemType = EItemType::ITEM_Potion;
	MaxCount = 0;
	CoolDown = 1.5f;
	ItemQuantity = 0;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Item/blue_layer.blue_layer'"));
	if (T2D_ICON.Object != NULL)
	{
		SlotTexture2D = T2D_ICON.Object;
	}
}

bool ULostArcItemPotionBase::Use(ALostArcCharacter* Character)
{
	if (Super::Use(Character))
	{
		return true;
	}
	return false;
}
