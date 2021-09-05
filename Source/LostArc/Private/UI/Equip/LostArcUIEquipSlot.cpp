// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equip/LostArcUIEquipSlot.h"
#include "Component/LostArcCharacterEquipComponent.h"

void ULostArcUIEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotType = ESlotType::Equip;
	SlotComponent = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->EquipComponent;
}

void ULostArcUIEquipSlot::RefreshSlotData(ULostArcAbilityBase* NewData)
{
	if (SlotData != nullptr) // Unbinding Delegate
	{
		UnBindSlotData();
	}

	Super::RefreshSlotData(NewData);

	if (NewData == nullptr)
	{
		Image_BG->SetVisibility(ESlateVisibility::Hidden);
	}

	else
	{
		auto SlotItem = dynamic_cast<ULostArcItemBase*>(SlotData);
		if (SlotItem == nullptr) return;

		if (SlotItem->GetBgTexture2D() != nullptr)
		{
			Image_BG->SetBrushFromTexture(SlotItem->GetBgTexture2D());
			Image_BG->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

