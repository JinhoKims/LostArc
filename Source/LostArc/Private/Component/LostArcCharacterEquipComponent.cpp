// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"


// Sets default values for this component's properties
ULostArcCharacterEquipComponent::ULostArcCharacterEquipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void ULostArcCharacterEquipComponent::InitializeComponent()
{
	Super::InitializeComponent();
	EarringSlot.SetNum(2);
	RingSlot.SetNum(2);
}

// Called when the game starts
void ULostArcCharacterEquipComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ULostArcCharacterEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ULostArcItemBase* ULostArcCharacterEquipComponent::EquipmentMounts(ULostArcItemEquipBase* NewEquip)
{
	if (NewEquip == nullptr) return nullptr;

	return nullptr;
}
