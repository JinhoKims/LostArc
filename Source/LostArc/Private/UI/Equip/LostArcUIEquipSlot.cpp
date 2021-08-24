// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equip/LostArcUIEquipSlot.h"
#include "Components/Image.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"

void ULostArcUIEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

FReply ULostArcUIEquipSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (EquipItem != nullptr)
		{
			EquipItem->Dismount(Cast<ALostArcCharacter>(GetOwningPlayerPawn()));
			return reply.NativeReply;
		}
	}

	return reply.NativeReply;
}

void ULostArcUIEquipSlot::BindEquipDelegate()
{
	Image_bgColor->SetBrushFromTexture(EquipItem->GetBgTexture2D());
	Image_bgColor->SetVisibility(ESlateVisibility::Visible);

	Image_Item->SetBrushFromTexture(EquipItem->GetItemTexture2D());
	Image_Item->SetVisibility(ESlateVisibility::Visible);
}

void ULostArcUIEquipSlot::ClearEquipDelegate()
{
	Image_bgColor->SetVisibility(ESlateVisibility::Hidden);
	Image_Item->SetVisibility(ESlateVisibility::Hidden);
	EquipItem = nullptr;
}
