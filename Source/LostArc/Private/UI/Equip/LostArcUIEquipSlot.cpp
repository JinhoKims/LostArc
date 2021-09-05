// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equip/LostArcUIEquipSlot.h"
#include "Component/LostArcCharacterEquipComponent.h"

void ULostArcUIEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotComponent = Cast<ALostArcCharacter>(GetOwningPlayerPawn())->EquipComponent;
}

void ULostArcUIEquipSlot::SetNativeTick(bool bCD)
{
	Super::SetNativeTick(bCD);
}

void ULostArcUIEquipSlot::RefreshSlotData(ULostArcAbilityBase* MovieSceneBlends)
{
	Super::RefreshSlotData(MovieSceneBlends);
}

void ULostArcUIEquipSlot::UnBindSlotData()
{
	Super::UnBindSlotData();
}
