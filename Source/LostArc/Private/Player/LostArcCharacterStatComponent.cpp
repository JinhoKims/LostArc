// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/LostArcCharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULostArcCharacterStatComponent::ULostArcCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	ManaRegenerationPerSecond = 5.0f;
	Level = 1;
}

void ULostArcCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

// Called when the game starts
void ULostArcCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	TimerDel.BindUFunction(this, FName("ManaRecovery"), ManaRegenerationPerSecond);
	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 2.0f, true);
}

void ULostArcCharacterStatComponent::ManaRecovery(float amount)
{
	SetMP(FMath::Clamp<float>(CurrentMP + amount, 0, CurrentStatData->Maxmp));
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
	if (ArcGameInstance != nullptr)
	{
		CurrentStatData = ArcGameInstance->GetArcCharacterData(NewLevel);
	}

	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		SetHP(CurrentHP = CurrentStatData->Maxhp);
		SetMP(CurrentMP = CurrentStatData->Maxmp);
	}
}

void ULostArcCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void ULostArcCharacterStatComponent::SetMP(float NewMP)
{
	CurrentMP = NewMP;
	OnMPChanged.Broadcast();
}

