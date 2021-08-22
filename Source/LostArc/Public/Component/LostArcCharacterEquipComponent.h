// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LostArcCharacterEquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARC_API ULostArcCharacterEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	TArray<class ULostArcItemBase*> equipSlot;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	ULostArcCharacterEquipComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	class ULostArcItemBase* EquipmentMounts(class ULostArcItemBase* NewEquip);

	
};
