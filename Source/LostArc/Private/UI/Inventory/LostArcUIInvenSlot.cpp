// Fill out your copyright notice in the Description page of Project Settings.

#include "Controller/LostArcPlayerController.h"
#include "UI/Inventory/LostArcUIInvenSlot.h"
#include "UI/LostArcUISlotDrag.h"
#include "Component/LostArcInventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if (SlotData)
		{
			if (!GetOwningPlayer()->GetWorldTimerManager().IsTimerActive(SlotData->AbilityCDProperty.Key)) 
			{
				reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			}
		}
	}
	return reply.NativeReply;
}

void ULostArcUIInvenSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (OutOperation == nullptr)
	{
		ULostArcUISlotDrag* oper = NewObject<ULostArcUISlotDrag>();
		UUserWidget* DraggedItem = CreateWidget<UUserWidget>(GetWorld(), DragVisualClass);
		UImage* ImageBox = Cast<UImage>(DraggedItem->GetWidgetFromName("Image_Item"));

		if (ImageBox != nullptr)
		{
			ImageBox->SetBrushFromTexture(SlotData->GetAbility_Icon());
		}

		oper->DefaultDragVisual = DraggedItem;
		oper->SlotIndex = this->SlotIndex;
		OutOperation = oper;
	}
}

bool ULostArcUIInvenSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	ULostArcUISlotDrag* owner = Cast<ULostArcUISlotDrag>(InOperation);
	Cast<ALostArcCharacter>(GetOwningPlayerPawn())->InventoryComponent->SwapSlot(owner->SlotIndex, this->SlotIndex);

	return true;
}

void ULostArcUIInvenSlot::UpdateQuantity()
{
	if (SlotData != nullptr) 
	{
		Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(dynamic_cast<ULostArcItemBase*>(SlotData)->GetItemQuantity())));
	}
}