// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "Abilities/Items/Equip/LostArcItemEquip_Earrings.h"

// Sets default values for this component's properties
ULostArcCharacterEquipComponent::ULostArcCharacterEquipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	for (int i = 0; i < 3; i++)
	{
		EquipTable.Add((EAccessoryType)i);
		EquipSlot.Add((EAccessoryType)i);
	}
}

void ULostArcCharacterEquipComponent::InitializeComponent()
{
	Super::InitializeComponent();

	/* EquipSlot.Find(EAccessoryType::Earring)->EquipArray.Add(NewObject<ULostArcItemEquipBase>(this, ULostArcItemEquip_Earrings::StaticClass()));
	EquipTable의 Key의 Value는 블루프린트(에디터)에서 설정해주는데 Init()는 에디터(블프) 실행 전에도 호출되어서 
	이 때 EquipTable의 Value를 가져올 수 없기에 직접 클래스정보(StaticClass)를 가져와야 한다. */

	
}

// Called when the game starts
void ULostArcCharacterEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < 3; i++)
	{
		EquipSlot.Find((EAccessoryType)i)->EquipArray.SetNum(EquipTable.Find((EAccessoryType)i)->GetDefaultObject()->MaxEqiupSlotCount);
	}
}

// Called every frame
void ULostArcCharacterEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ULostArcItemEquipBase* ULostArcCharacterEquipComponent::GetEquipItem(EAccessoryType Type, int32 Index)
{
	return EquipSlot.Find(Type)->EquipArray[Index];	
}

void ULostArcCharacterEquipComponent::DismountEquip(ULostArcItemEquipBase* OwnerEquip, int32 Index)
{
	if (EquipSlot.Find(OwnerEquip->GetType())->EquipArray[Index] == nullptr) return;

	EquipSlot.Find(OwnerEquip->GetType())->EquipArray[Index] = nullptr;
	EquipSlotUpdate.Broadcast(OwnerEquip->GetType(), Index);
	Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->MoveItem(OwnerEquip);
}

void ULostArcCharacterEquipComponent::EquipMounts(ULostArcItemEquipBase* NewEquip)
{
	if (NewEquip == nullptr) return;

	for (int32 i = 0; i < NewEquip->MaxEqiupSlotCount; i++) // When an empty slot exists
	{
		if (EquipSlot.Find(NewEquip->GetType())->EquipArray[i] == nullptr)
		{
			EquipSlot.Find(NewEquip->GetType())->EquipArray[i] = NewEquip;
			EquipSlotUpdate.Broadcast(NewEquip->GetType(), i);
			return;
		}
	}
	
	// When all slots are fully
	Swap(EquipSlot.Find(NewEquip->GetType())->EquipArray[0], NewEquip);
	EquipSlotUpdate.Broadcast(NewEquip->GetType(), 0);
	Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->MoveItem(NewEquip);
}	