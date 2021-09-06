// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LostArcUIInvenSlot.h"
#include "Component/LostArcInventoryComponent.h"

void ULostArcUIInvenSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotType = ESlotType::Inven;
	SlotComponent = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->InventoryComponent;
}

bool ULostArcUIInvenSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if(!Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		ULostArcUISlotDrag* Owner = Cast<ULostArcUISlotDrag>(InOperation);
		auto Interface = Cast<ILostArcCharacterInterface>(SlotComponent);
		
		if (Interface != nullptr)
		{
			Interface->SwappingSlot(Owner->SlotComponent, Owner->SlotIndex, this->SlotIndex);
			return true;
		}
	}

	return false;
}

void ULostArcUIInvenSlot::RefreshSlotData(ULostArcAbilityBase* NewData)
{
	if (SlotData != nullptr) // Unbinding Delegate
	{
		UnBindSlotData();		
	}

	Super::RefreshSlotData(NewData);
	
	if (NewData != nullptr)
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
		ItemQuantityHandle = SlotItem->QuantityUpdate.AddUObject(this, &ULostArcUIInvenSlot::UpdateQuantity);
	}
}

void ULostArcUIInvenSlot::UnBindSlotData()
{
	Super::UnBindSlotData();
	
	Image_BG->SetVisibility(ESlateVisibility::Hidden);
	Text_Quantity->SetVisibility(ESlateVisibility::Hidden);

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