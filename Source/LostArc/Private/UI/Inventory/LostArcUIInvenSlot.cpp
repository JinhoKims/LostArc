// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LostArcUIInvenSlot.h"
#include "Component/LostArcInventoryComponent.h"

void ULostArcUIInvenSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotComponent = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->InventoryComponent;
}

void ULostArcUIInvenSlot::SetNativeTick(bool CD)
{
	Super::SetNativeTick(CD);
}

void ULostArcUIInvenSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULostArcUIInvenSlot::RefreshSlotData(ULostArcAbilityBase* NewData)
{
	if (SlotData != nullptr) // Unbinding Delegate
	{
		UnBindSlotData();		
	}

	Super::RefreshSlotData(NewData);

	if (NewData == nullptr)
	{
		Image_BG->SetVisibility(ESlateVisibility::Hidden);
		Text_Quantity->SetVisibility(ESlateVisibility::Hidden);
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
		if (SlotItem->IsConsumable())
		{
			UpdateQuantity();
			Text_Quantity->SetVisibility(ESlateVisibility::Visible);
		}

		AbilityCDHandle = SlotData->AbilityCDProperty.Value.AddUObject(this, &ULostArcUIInvenSlot::SetNativeTick);
		ItemQuantityHandle = SlotItem->QuantityUpdate.AddUObject(this, &ULostArcUIInvenSlot::UpdateQuantity);
	}
}

void ULostArcUIInvenSlot::UnBindSlotData()
{
	Super::UnBindSlotData();
	auto SlotItem = dynamic_cast<ULostArcItemBase*>(SlotData);
	
	if (SlotItem != nullptr)
	{
		SlotItem->QuantityUpdate.Remove(ItemQuantityHandle);
	}
}

void ULostArcUIInvenSlot::UpdateQuantity()
{
	if (SlotData != nullptr) 
	{
		Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(dynamic_cast<ULostArcItemBase*>(SlotData)->GetItemQuantity())));
	}
}