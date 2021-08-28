// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LostArcUIInvenSlot.h"

void ULostArcUIInvenSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULostArcUIInvenSlot::SetNativeTick(bool CD)
{
	Super::SetNativeTick(CD);
}

void ULostArcUIInvenSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void ULostArcUIInvenSlot::SetSlotData(ULostArcAbilityBase* NewData)
{
	Super::SetSlotData(NewData);

	SlotItem = dynamic_cast<ULostArcItemBase*>(SlotData);
	if (SlotItem == nullptr) return;

	if (SlotItem->GetBgTexture2D() != nullptr)
	{
		Image_BG->SetBrushFromTexture(SlotItem->GetBgTexture2D());
		Image_BG->SetVisibility(ESlateVisibility::Visible);
	}

	if (SlotItem->GetMaxCount() <= 0)
	{
		UpdateQuantity();
		Text_Quantity->SetVisibility(ESlateVisibility::Visible);
	}

	NewData->AbilityCDProperty.Value.AddUObject(this, &ULostArcUIInvenSlot::SetNativeTick);
	SlotItem->ItemQuantityUpdate.AddUObject(this, &ULostArcUIInvenSlot::UpdateQuantity);
}
void ULostArcUIInvenSlot::UpdateQuantity()
{
	if (SlotData != nullptr) 
	{
		Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(SlotItem->GetItemQuantity())));
	}
}