#include "Component/LostArcQuickSlotComponent.h"

ULostArcQuickSlotComponent::ULostArcQuickSlotComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	QuickSlot.SetNum(16);
}

void ULostArcQuickSlotComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
}

void ULostArcQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ULostArcQuickSlotComponent::UseAbility(int32 SlotIndex)
{
	
}