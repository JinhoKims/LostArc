// Fill out your copyright notice in the Description page of Project Settings.

#include "LostArcCharacterStatComponent.h"
#include "LostArcGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULostArcCharacterStatComponent::ULostArcCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	Level = 1;
}

void ULostArcCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(1);
}

// Called when the game starts
void ULostArcCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void ULostArcCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULostArcCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto ArcGameInstance = Cast<ULostArcGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentStatData = ArcGameInstance->GetArcCharacterData(NewLevel);

	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		CurrentHP = CurrentStatData->Maxhp;
		CurrentMP = CurrentStatData->Maxmp;
	}
}

