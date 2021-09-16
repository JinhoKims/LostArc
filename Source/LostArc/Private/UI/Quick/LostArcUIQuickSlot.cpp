// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Quick/LostArcUIQuickSlot.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "Component/LostArcCharacterInterface.h"
#include "Component/LostArcQuickSlotComponent.h"

void ULostArcUIQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	SlotType = ESlotType::Quick;
	Text_Key->SetText(KeyName);
}

bool ULostArcUIQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto OwnerDrag = Cast<ULostArcUISlotDrag>(InOperation);
	if(OwnerDrag == nullptr) return false;

	switch (QuickSlotType)
	{
	case EQuickSlotType::Ability:
		break;

	case EQuickSlotType::Potion:
		ILostArcCharacterInterface * Interface = Cast<ILostArcCharacterInterface>(OwnerDrag->SlotComponent);
		if(Cast<ULostArcItemEquipBase>(Interface->GetAbility(OwnerDrag->SlotIndex))) return false;
		
		if(OwnerDrag->SlotType == ESlotType::Inven)
		{
			auto OwnerItem = Cast<ULostArcItemBase>(Interface->GetAbility(OwnerDrag->SlotIndex));
			RefreshSlotData(OwnerItem);
			
			RefIndex = OwnerDrag->SlotIndex;
			ItemQuantityHandle = OwnerItem->QuantityUpdate.AddUObject(this, &ULostArcUIQuickSlot::UpdateQuantity);
			Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(OwnerItem->GetItemQuantity())));
			Text_Quantity->SetVisibility(ESlateVisibility::Visible);
			Cast<ALostArcCharacter>(GetOwningPlayerPawn())->QuickSlotComponent->QuickSlot[SlotIndex] = Interface->GetAbility(OwnerDrag->SlotIndex);
		}
		break;
	}
	// 퀵 슬롯끼리 교환하려면 결국엔 QuickComponent에서 SappingSlot 오버라이딩이 필요
	// 그리고 아이템 카운트가 0 될 때 델리게이트로 퀵슬롯의 아이템도 삭제 필요 (퀵 슬롯을 아이템 / 스킬별로 각각 구현) 
	return false;
}


void ULostArcUIQuickSlot::RefreshSlotData(ULostArcAbilityBase* NewData)
{
	if(SlotData != nullptr)
	{
		UnBindSlotData();
	}
	
	Super::RefreshSlotData(NewData);
	
	UpdateQuantity();
}

void ULostArcUIQuickSlot::UnBindSlotData()
{
	Super::UnBindSlotData();
	
	auto SlotItem = Cast<ULostArcItemBase>(SlotData);
	if (SlotItem != nullptr)
	{
		SlotItem->QuantityUpdate.Remove(ItemQuantityHandle);
	}
}

void ULostArcUIQuickSlot::UpdateQuantity()
{
	if (SlotData != nullptr) 
	{
		Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(Cast<ULostArcItemBase>(SlotData)->GetItemQuantity())));
	}
}