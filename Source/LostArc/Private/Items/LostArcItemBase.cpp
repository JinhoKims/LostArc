// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LostArcItemBase.h"

bool ULostArcItemBase::IsConsumable() const
{
	if (MaxCount <= 0)
	{
		return true;
	}
	return false;
}

EItemType ULostArcItemBase::GetItemType() const
{
	return ItemType;
}
