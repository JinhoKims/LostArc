// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LostArcItemBase.h"

bool ULostArcItemBase::Use(ALostArcCharacter* Character)
{
	return false;
}

bool ULostArcItemBase::IsConsumable() const
{
	if (MaxCount <= 0)
	{
		return true;
	}
	return false;
}
