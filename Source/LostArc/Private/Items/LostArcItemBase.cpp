// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/LostArcItemBase.h"

bool ULostArcItemBase::IsConsumable() const
{
	if (MaxCount <= 0) // MaxCount가 0이면 소모품(무제한)
	{
		return true;
	}
	return false;
}

EItemType ULostArcItemBase::GetItemType() const
{
	return ItemType;
}

bool ULostArcItemBase::Use(ALostArcCharacter* Character)
{
	if (AbilityStateCheck(Character))
	{
		PreCast(Character);
		return true;
	}
	else
		return false;
}

bool ULostArcItemBase::AbilityStateCheck(ALostArcCharacter* Character)
{
	if (Character->GetWorldTimerManager().IsTimerActive(AbilityCDProperty.Key))
	{
		UE_LOG(LogTemp, Warning, TEXT("CoolDown Left is : %f"), Character->GetWorldTimerManager().GetTimerRemaining(AbilityCDProperty.Key));
		return true;
	}
	return false;
}

void ULostArcItemBase::AddItemCount(int32 Count)
{
	ItemQuantity += Count;
}

void ULostArcItemBase::PreCast(ALostArcCharacter* Character)
{
	Character->GetWorldTimerManager().SetTimer(AbilityCDProperty.Key, FTimerDelegate::CreateLambda([=]() {AbilityCDProperty.Value.Broadcast(false); }), CoolDown, false);
	AbilityCDProperty.Value.Broadcast(true);
}
