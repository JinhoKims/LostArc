// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LostArcQuickSlotComponent.h"

// Sets default values for this component's properties
ULostArcQuickSlotComponent::ULostArcQuickSlotComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	
}


// Called when the game starts
void ULostArcQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULostArcQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

