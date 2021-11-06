#include "Component/LostArcQuickSlotComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Skill/LostArcSkillBase.h"
#include "Component/LostArcInventoryComponent.h"

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

ULostArcAbilityBase* ULostArcQuickSlotComponent::GetAbility(int32 SlotIndex, bool bTrans)
{
	if(!bTrans)
	{
		return QuickSlot[SlotIndex];
	}
	else
	{
		auto TransUnit = QuickSlot[SlotIndex];
		QuickSlot[SlotIndex] = nullptr;
		return TransUnit;
	}
}

void ULostArcQuickSlotComponent::UseAbility(int32 SlotIndex)
{
	if (QuickSlot[SlotIndex] != nullptr)
	{
		if(SlotIndex < 8) // Skills
		{
			
		}
		else // Items
		{
			if(QuickSlot[SlotIndex]->Use(Cast<ALostArcCharacter>(GetOwner())))
			{
				Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->DeleteItemAfterCheckingQuantity();
				// 인벤토리 전체를 스캔해서 current가 0인 슬롯을 삭제
			}
		}
	}
}

void ULostArcQuickSlotComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent)
{
}
