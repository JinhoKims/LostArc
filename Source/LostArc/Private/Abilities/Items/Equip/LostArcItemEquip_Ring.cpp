// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Items/Equip/LostArcItemEquip_Ring.h"

ULostArcItemEquip_Ring::ULostArcItemEquip_Ring(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
    ItemName = FString("Equip_Ring");

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Item/acc_16.acc_16'"));
	if (T2D_ICON.Object != NULL)
	{
		ItemTexture2D = T2D_ICON.Object;
	}
}

bool ULostArcItemEquip_Ring::Use(ALostArcCharacter* Character)
{
	if (Super::Use(Character))
	{
		auto StatComponent = Character->StatComponent;
		StatComponent->SetCurrentAttributeValue(EAttributeType::ATK, StatComponent->GetCurrnetAttributeValue(EAttributeType::ATK) + Value);
		return true;
	}
	return false;
}