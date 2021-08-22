// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Items/Equip/LostArcItemEquip_Earrings.h"
#include "Component/LostArcInventoryComponent.h"

ULostArcItemEquip_Earrings::ULostArcItemEquip_Earrings(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	ItemName = FString("Equip_Earrings");

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Item/Equip/acc_109.acc_109'"));
	if (T2D_ICON.Object != NULL)
	{
		ItemTexture2D = T2D_ICON.Object;
	}
}

bool ULostArcItemEquip_Earrings::Use(ALostArcCharacter* Character)
{
	for (int i = 0; i < 2; i++)
	{
		if (Character->EquipComponent->EarringSlot[i] == nullptr)
		{
			Character->EquipComponent->EarringSlot[i] = this;
			auto StatComponent = Character->StatComponent;
			StatComponent->AddBonusAttribute(EAttributeType::ATK, Value);
			return true;
		}
	}

	ULostArcItemEquipBase* temp = this;
	Swap(Character->EquipComponent->EarringSlot[0], temp);

	return true;
}
