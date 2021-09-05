// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LostArcCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULostArcCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class LOSTARC_API ILostArcCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UseAbility(int32 SlotIndex) = 0;
	virtual void SwappingSlot(int32 OwnerIndex, int32 DistIndex) {}
	virtual bool ReceiveSlot(int32 OwnerIndex, int32 DistIndex) { return true; }
};
