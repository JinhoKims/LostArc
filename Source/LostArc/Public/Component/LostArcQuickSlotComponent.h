#pragma once

#include "CoreMinimal.h"
#include "LostArcCharacterInterface.h"
#include "Components/ActorComponent.h"
#include "LostArcQuickSlotComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARC_API ULostArcQuickSlotComponent : public UActorComponent, public ILostArcCharacterInterface
{
	GENERATED_BODY()

public:	
	ULostArcQuickSlotComponent();
	virtual void UseAbility(int32 SlotIndex) override;
	virtual void SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent) override;

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TArray<class ULostArcAbilityBase*> QuickSlot;
	
	const int32 MaxSlotCount = 16; 
};
