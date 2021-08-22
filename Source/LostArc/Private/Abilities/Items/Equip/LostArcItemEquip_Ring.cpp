// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Items/Equip/LostArcItemEquip_Ring.h"
#include "Component/LostArcInventoryComponent.h"

ULostArcItemEquip_Ring::ULostArcItemEquip_Ring(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
    ItemName = FString("Equip_Ring");

	static ConstructorHelpers::FObjectFinder<UTexture2D> T2D_ICON(TEXT("Texture2D'/Game/Icons/Item/Equip/acc_16.acc_16'"));
	if (T2D_ICON.Object != NULL)
	{
		ItemTexture2D = T2D_ICON.Object;
	}
}

bool ULostArcItemEquip_Ring::Use(ALostArcCharacter* Character)
{
	for (int i = 0; i < 2; i++)
	{
		if (Character->EquipComponent->RingSlot[i] == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Slot Index : %d"),GetInventoryIndex());
			Character->EquipComponent->RingSlot[i] = this;
			auto StatComponent = Character->StatComponent;
			StatComponent->AddBonusAttribute(EAttributeType::DEF, Value);
			Character->InventoryComponent->InventorySlotChangeNullptr(GetInventoryIndex());
			return true;
		}
	}

	ULostArcItemEquipBase* temp = this;
	UE_LOG(LogTemp, Warning, TEXT("AAK"));
	Swap(Character->EquipComponent->RingSlot[0], temp);



	return true;
}