// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/LostArcCharacterStatComponent.h"
#include "UI/LostArcUIProgressBar.h"
#include "Kismet/GameplayStatics.h"

ULostArcCharacterStatComponent::ULostArcCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	IncreasedManaRegeneration = 5.0f;
}

void ULostArcCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	Level = 1;
	SetNewLevel(Level);
}

void ULostArcCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	ManaRegenerationTimerDelegate.BindUFunction(this, FName("ManaRegenerationPerSecond"), IncreasedManaRegeneration);
	GetOwner()->GetWorldTimerManager().SetTimer(ManaRegenerationTimerHandle, ManaRegenerationTimerDelegate, 2.0f, true);
}

void ULostArcCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULostArcCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto ArcGameInstance = Cast<ULostArcGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (ArcGameInstance != nullptr)
	{
		CurrentStatData = ArcGameInstance->GetArcCharacterData(NewLevel);
		if (CurrentStatData != nullptr)
		{
			Level = NewLevel;
			SetHP(CurrentHP = CurrentStatData->Maxhp);
			SetMP(CurrentMP = CurrentStatData->Maxmp);
			OnProgressBarChanged.Broadcast(EBarType::HP);
			OnProgressBarChanged.Broadcast(EBarType::MP);
		}
	}
}

void ULostArcCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnProgressBarChanged.Broadcast(EBarType::HP);
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void ULostArcCharacterStatComponent::SetMP(float NewMP)
{
	CurrentMP = NewMP;
	OnProgressBarChanged.Broadcast(EBarType::MP);
}

void ULostArcCharacterStatComponent::ManaRegenerationPerSecond(float Amount)
{
	SetMP(FMath::Clamp<float>(CurrentMP + Amount, 0, CurrentStatData->Maxmp));
}