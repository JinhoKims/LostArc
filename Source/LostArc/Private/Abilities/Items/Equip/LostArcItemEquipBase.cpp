// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Items/Equip/LostArcItemEquipBase.h"

ULostArcItemEquipBase::ULostArcItemEquipBase(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	ItemType = EItemType::ITEM_Equip;
	MaxCount = 1;
	CoolDown = 0.f;
	ItemQuantity = 1;
}

bool ULostArcItemEquipBase::Use(ALostArcCharacter* Character)
{
	if (Super::Use(Character))
	{
		return true;
	}
	return false;
}