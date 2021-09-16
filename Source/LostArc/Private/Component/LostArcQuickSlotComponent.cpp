#include "Component/LostArcQuickSlotComponent.h"

#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Skill/LostArcSkillBase.h"

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
	if (QuickSlot[SlotIndex] != nullptr)
	{
		if(SlotIndex < 8)
		{
			
		}
		else
		{
			
		}
		QuickSlot[SlotIndex]->Use(Cast<ALostArcCharacter>(GetOwner()));
	}
}

void ULostArcQuickSlotComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent)
{
	

	
}
