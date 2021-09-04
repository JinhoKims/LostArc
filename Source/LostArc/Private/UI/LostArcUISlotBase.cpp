	// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LostArcUISlotBase.h"
#include "UI/LostArcUISlotDrag.h"
#include "Component/LostArcInventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ULostArcUISlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	bEnableTick = false;
	SlotIndex = 0;
}

void ULostArcUISlotBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bEnableTick) 
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
		auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

		if (GetOwningPlayer()->GetWorldTimerManager().IsTimerActive(SlotData->AbilityCDProperty.Key))
		{
			float Value = GetOwningPlayer()->GetWorldTimerManager().GetTimerRemaining(SlotData->AbilityCDProperty.Key) / SlotData->GetCDTime();
			Image_CD->GetDynamicMaterial()->SetScalarParameterValue(FName(TEXT("Progress")), Value < 0.002f ? 0.0f : Value);
		}
	}
}

FReply ULostArcUISlotBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (SlotData)
		{
			auto Inter = Cast<ILostArcCharacterInterface>(SlotComponent);
			if (Inter)
			{
				Inter->UseAbility(SlotIndex);
				return reply.NativeReply;
			}
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

void ULostArcUISlotBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
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

bool ULostArcUISlotBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	ULostArcUISlotDrag* Owner = Cast<ULostArcUISlotDrag>(InOperation);
	auto Inter = Cast<ILostArcCharacterInterface>(SlotComponent);

	if (Inter)
	{
		Inter->SwappingSlot(Owner->SlotIndex, this->SlotIndex);
	}

	return true;
}

void ULostArcUISlotBase::SetNativeTick(bool CD)
{
	bEnableTick = CD;

	if (CD)
	{
		Image_CD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Image_CD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULostArcUISlotBase::RefreshSlotData(ULostArcAbilityBase* NewData)
{
	if (NewData == nullptr)
	{
		SlotData = nullptr;
		Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SlotData = NewData;

		if (SlotData->GetAbility_Icon() != nullptr)
		{
			Image_Icon->SetBrushFromTexture(SlotData->GetAbility_Icon());
			Image_Icon->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ULostArcUISlotBase::UnBindSlotData()
{
	if (SlotData != nullptr)
	{
		SlotData->AbilityCDProperty.Value.Remove(AbilityCDHandle);
	}
}