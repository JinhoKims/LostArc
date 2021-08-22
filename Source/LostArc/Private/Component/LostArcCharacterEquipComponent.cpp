// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"
#include "Abilities/Items/LostArcItemBase.h"

// Sets default values for this component's properties
ULostArcCharacterEquipComponent::ULostArcCharacterEquipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

// Called when the game starts
void ULostArcCharacterEquipComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULostArcCharacterEquipComponent::InitializeComponent()
{
	Super::InitializeComponent();
	equipSlot.SetNum(5);
}

// Called every frame
void ULostArcCharacterEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ULostArcItemBase* ULostArcCharacterEquipComponent::EquipmentMounts(ULostArcItemBase* NewEquip)
{
	if (NewEquip == nullptr) return nullptr;

	for (int i = 0; i < 5; i++) // 장비창에 빈 슬롯이 있는 경우
	{
		if (equipSlot[i] == nullptr)
		{
			equipSlot[i] = NewEquip;
			return nullptr;
		}
	}

	Swap(equipSlot[0], NewEquip);
	return NewEquip;
}
