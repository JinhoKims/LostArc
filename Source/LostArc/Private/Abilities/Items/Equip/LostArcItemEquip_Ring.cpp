// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Items/Equip/LostArcItemEquip_Ring.h"

ULostArcItemEquip_Ring::ULostArcItemEquip_Ring(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	Name = FString("Equip_Ring");
	MaxEqiupSlotCount = 2;
	Type = EAccessoryType::Ring;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Item/Equip/acc_16.acc_16'"));
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
		StatComponent->AddBonusAttribute(EAttributeType::DEF, Value);
	}

	return true;
}

void ULostArcItemEquip_Ring::Dismount(ALostArcCharacter* Character)
{
	Super::Dismount(Character);
	auto StatComponent = Character->StatComponent;
	StatComponent->AddBonusAttribute(EAttributeType::DEF, -Value);
}
