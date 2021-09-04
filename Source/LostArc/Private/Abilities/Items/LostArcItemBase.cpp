// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Items/LostArcItemBase.h"
#include "Component/LostArcInventoryComponent.h"

bool ULostArcItemBase::IsConsumable() const
{
	if (MaxCount <= 0) // MaxCount가 0 이하면 소모품(무제한)
	{
		return true;
	}
	return false;
}

bool ULostArcItemBase::Use(ALostArcCharacter* Character)
{
	return AbilityStateCheck(Character);
}

bool ULostArcItemBase::AbilityStateCheck(ALostArcCharacter* Character)
{
	if (Character->GetWorldTimerManager().IsTimerActive(AbilityCDProperty.Key))
	{
		UE_LOG(LogTemp, Warning, TEXT("CoolDown Left is : %f"), Character->GetWorldTimerManager().GetTimerRemaining(AbilityCDProperty.Key));
		return false;
	}

	return true;
}

bool ULostArcItemBase::SetItemQuantity(int32 Count)
{
	ItemQuantity += Count;
	QuantityUpdate.Broadcast();

	return bool(FMath::Clamp(ItemQuantity, 0, 1));
}


