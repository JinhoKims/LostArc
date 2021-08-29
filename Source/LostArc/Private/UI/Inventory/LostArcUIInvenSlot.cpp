// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LostArcUIInvenSlot.h"
#include "Component/LostArcInventoryComponent.h"

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

FReply ULostArcUIInvenSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	auto OwingCharacter = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (SlotData)
		{
			OwingCharacter->InventoryComponent->UseItem(SlotIndex);
			return reply.NativeReply;
		}
	}
	//else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	//{
	//	reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	//}
	return reply.NativeReply;
}

void ULostArcUIInvenSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{

}

bool ULostArcUIInvenSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}


void ULostArcUIInvenSlot::SetSlotData(ULostArcAbilityBase* NewData)
{
	Super::SetSlotData(NewData);

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

	NewData->AbilityCDProperty.Value.AddUObject(this, &ULostArcUIInvenSlot::SetNativeTick);
	SlotItem->ItemQuantityUpdate.AddUObject(this, &ULostArcUIInvenSlot::UpdateQuantity);
}

void ULostArcUIInvenSlot::ClearSlotData()
{
	Super::ClearSlotData();

	Image_BG->SetVisibility(ESlateVisibility::Hidden);
	Text_Quantity->SetVisibility(ESlateVisibility::Hidden);
}

void ULostArcUIInvenSlot::UpdateQuantity()
{
	if (SlotData != nullptr) 
	{
		Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(dynamic_cast<ULostArcItemBase*>(SlotData)->GetItemQuantity())));
	}
}