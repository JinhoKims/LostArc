// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Items/LostArcItemPotion_Mana.h"

ULostArcItemPotion_Mana::ULostArcItemPotion_Mana(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ItemName = FString("Potion_Mana");

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Item/battle_item_01_24.battle_item_01_24'"));
	if (T2D_ICON.Object != NULL)
	{
		ItemTexture2D = T2D_ICON.Object;
	}
}

bool ULostArcItemPotion_Mana::Use(ALostArcCharacter* Character)
{
	if (Super::Use(Character))
	{
		auto StatComponent = Character->StatComponent;
		StatComponent->SetCurrentAttributeValue(EAttributeType::MP, FMath::Clamp(StatComponent->GetCurrnetAttributeValue(EAttributeType::MP) + Value, 1.f, StatComponent->GetMaxAttributeValue(EAttributeType::HP)));
		return true;
	}
	return false;
}
