// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArcCharacterInterface.h"
#include "Components/ActorComponent.h"
#include "LostArcQuickSlotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARC_API ULostArcQuickSlotComponent : public UActorComponent, ILostArcCharacterInterface
{
	GENERATED_BODY()

public:	
	ULostArcQuickSlotComponent();

protected:	
	virtual void BeginPlay() override;

public:	
	
		
};
