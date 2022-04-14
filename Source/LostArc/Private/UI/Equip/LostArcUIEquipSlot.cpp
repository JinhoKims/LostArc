	// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equip/LostArcUIEquipSlot.h"

#include "Abilities/Skill/LostArcSkillBase.h"
#include "Component/LostArcAbilityInterface.h"
#include "Component/LostArcCharacterEquipComponent.h"
#include "Component/LostArcInventoryComponent.h"
#include "Controller/LostArcPlayerController.h"

	void ULostArcUIEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotType = ESlotType::Equip;
	SlotComponent = Cast<ALostArcPlayerCharacter>(GetOwningPlayerPawn())->EquipComponent;
}

bool ULostArcUIEquipSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	ULostArcUISlotDrag* Owner = Cast<ULostArcUISlotDrag>(InOperation);
	
	if(!Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto Interface = Cast<ILostArcAbilityInterface>(SlotComponent);
		
		if (Interface != nullptr)
		{
			Interface->SwappingSlot(Owner->SlotIndex, this->SlotIndex, Owner->SlotComponent);
			return true;
		}
	}
	
	if(Owner->SlotType == ESlotType::Equip)
		return true;
	else
		return false;
}

void ULostArcUIEquipSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto Inter = Cast<ILostArcAbilityInterface>(SlotComponent);

	if(Inter != nullptr)
	{
		Inter->UseAbility(SlotIndex);
	}
}

FReply ULostArcUIEquipSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp,Warning,TEXT("Equip click"));

	if(ULostArcSkillBase::bAnimationRunning)
		return Super::Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if(Cast<ULostArcSkillBase>(SlotData))
		return Super::Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)) // Right Mouse Clicked
	{
		Cast<ALostArcPlayerController>(GetOwningPlayer())->bOnSlotClick = true;
		auto APlayer = Cast<ALostArcPlayerCharacter>(GetOwningPlayerPawn());
		
		if(APlayer->InventoryComponent->InventorySlotEmptyCheck())
		{
			return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
		}
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
		
	return Super::Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
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

