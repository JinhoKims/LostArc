// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LostArcItemPotionBase.h"


ULostArcItemPotionBase::ULostArcItemPotionBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ItemType = EItemType::ITEM_Potion;
	MaxCount = 0;
}