// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory//LostArcUIInventorySlot.h"
#include "UI/LostArcUIMainHUD.h"
#include "Controller/LostArcPlayerController.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcInventoryComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "UI/LostArcUISlotDrag.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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

	if (Item->GetBgTexture2D() != nullptr)
	{
		Image_bgColor->SetBrushFromTexture(Item->GetBgTexture2D());
		Image_bgColor->SetVisibility(ESlateVisibility::Visible);
	}

	Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(Item->GetItemQuantity())));
	if (Item->GetMaxCount() <= 0)
	{
		Text_Quantity->SetVisibility(ESlateVisibility::Visible);
	}
}

void ULostArcUIInventorySlot::UpdateItemQuantity()
{
	if (Item != nullptr)
	{
		Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(Item->GetItemQuantity())));
	}
}

void ULostArcUIInventorySlot::ClearItemDelegate()
{
	Text_Quantity->SetVisibility(ESlateVisibility::Hidden);
	Image_bgColor->SetVisibility(ESlateVisibility::Hidden);
	Image_Item->SetVisibility(ESlateVisibility::Hidden);

	Item = nullptr;
}

FReply ULostArcUIInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	auto Char = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (Item)
		{
			Item->Use(Cast<ALostArcCharacter>(GetOwningPlayerPawn()));
			return reply.NativeReply;
		}
	}

	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}

	return reply.NativeReply;
}

void ULostArcUIInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (OutOperation == nullptr)
	{
		ULostArcUISlotDrag* oper = NewObject<ULostArcUISlotDrag>();
		OutOperation = oper;
		oper->FromNum = Item->GetInventorySlotIndex();
		oper->SlotType = Item->GetItemType();
		
		if (DragVisualClass != nullptr) // 드래그할 때 새로 만들 따라다니는 위젯(기존 위젯은 Hidden 처리)
		{
			ULostArcUIInventorySlot* visual = CreateWidget<ULostArcUIInventorySlot>(Cast<APlayerController>(GetOwningPlayer()), DragVisualClass);
			visual->Item = Item;
			oper->DefaultDragVisual = visual;
		}
	}


}

bool ULostArcUIInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	ULostArcUISlotDrag* oper = Cast<ULostArcUISlotDrag>(InOperation); // 드래그한 슬롯의 정보
	// this->item : 드래그한 지점에 있는 슬롯의 정보
	
	auto Inven = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->InventoryComponent;
	if (oper != nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("%d"), this->Item->GetInventorySlotIndex()); -> 모든 슬롯에 번호 지정 필요!! (지금은 현재 아이템 멤버에 슬롯 번호를 기입함)
		UE_LOG(LogTemp, Warning, TEXT("%d"), Inven->GetSlotItem(oper->FromNum)->GetInventorySlotIndex()); // 드래그한 슬롯의 번호를 출력(아이템의 멤버를 이용해)
		return true;
	}

	else
	{
		return false;
	}
}