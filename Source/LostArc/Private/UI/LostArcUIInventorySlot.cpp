// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIInventorySlot.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcInventoryComponent.h"
#include "Items/LostArcItemBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void ULostArcUIInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULostArcUIInventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bEnableTick)
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
		auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

		float Value = GetOwningPlayer()->GetWorldTimerManager().GetTimerRemaining(Item->AbilityCDProperty.Key) / Item->GetCDTime();
		Image_CoolDown->GetDynamicMaterial()->SetScalarParameterValue(FName(TEXT("Progress")), Value < 0.002f ? 0.0f : Value);
	}
}

void ULostArcUIInventorySlot::SetNativeTick(bool CD)
{
	bEnableTick = CD;

	if (CD)
	{
		Image_CoolDown->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Image_CoolDown->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULostArcUIInventorySlot::BindItemDelegate()
{
	Item->AbilityCDProperty.Value.AddUObject(this, &ULostArcUIInventorySlot::SetNativeTick);
	Item->ItemQuantityUpdate.AddUObject(this, &ULostArcUIInventorySlot::UpdateItemQuantity);

	if (Item->GetItemTexture2D() != nullptr)
	{
		Image_Item->SetBrushFromTexture(Item->GetItemTexture2D());
		Image_Item->SetVisibility(ESlateVisibility::Visible);
	}

	if (Item->GetSlotTexture2D() != nullptr)
	{
		Image_Slot->SetBrushFromTexture(Item->GetSlotTexture2D());
	}

	Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(Item->GetItemQuantity())));
	Text_Quantity->SetVisibility(ESlateVisibility::Visible);
}

void ULostArcUIInventorySlot::UpdateItemQuantity()
{
	Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(Item->GetItemQuantity())));
}

FReply ULostArcUIInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (Item)
		{
			Item->Use(Cast<ALostArcCharacter>(GetOwningPlayerPawn()));
		}
	}

	return reply.NativeReply;
}