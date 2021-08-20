// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LostArcCharacterEquipComponent.h"

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

	equipSlot.SetNum(4);
}


// Called every frame
void ULostArcCharacterEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

