// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LostArcInventoryComponent.h"
#include "Items/LostArcItemBase.h"

#include "Items/LostArcItemPotionBase.h"

// Sets default values for this component's properties
ULostArcInventoryComponent::ULostArcInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	ItemClass.Init(ULostArcItemBase::StaticClass(), 10);
}

void ULostArcInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (int i = 0; i < 5; i++)
	{
		DataTable.Add(ItemClass[i].GetDefaultObject()->ItemName, NewObject<ULostArcItemBase>(this, ItemClass[i].Get())); // 데이터 테이블에 모든 아이템 정보를 넣는다.
	}
}

// Called when the game starts
void ULostArcInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	AddPickupItem(DataTable.Find("Potion_Health"), 10);
	AddPickupItem(DataTable.Find("Potion_Health"), 10);
	AddPickupItem(DataTable.Find("Potion_Health"), 10);
	AddPickupItem(DataTable.Find("Potion_Health"), 10);

	UE_LOG(LogTemp, Warning, TEXT("======================="));
	
	AddPickupItem(DataTable.Find("Potion_Mana"), 10);
	AddPickupItem(DataTable.Find("Potion_Mana"), 10);
	AddPickupItem(DataTable.Find("Potion_Mana"), 10);
	
	UE_LOG(LogTemp, Warning, TEXT("======================="));
	
	AddPickupItem(DataTable.Find("Potion_Health"), 10);
	AddPickupItem(DataTable.Find("Potion_Mana"), 10);

	UE_LOG(LogTemp, Warning, TEXT("======================="));

	AddPickupItem(DataTable.Find("Potdfs"), 10);
	AddPickupItem(DataTable.Find("zxcs"), 10);
	AddPickupItem(DataTable.Find("Potion"), 10);
}

void ULostArcInventoryComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	InventoryData.Empty();
}

// Called every frame
void ULostArcInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULostArcInventoryComponent::AddPickupItem(ULostArcItemBase** NewItem, int32 ItemCount)
{
	if (NewItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewItem is nullptr"));
		return;
	}

	FLostArcItemData* FoundItem = InventoryData.Find(*NewItem); // 인벤토리 서치
	auto ItemData = *NewItem;

	if (FoundItem) // 인벤토리에 같은 아이템이 존재한다면
	{
		if (ItemData->GetItemType() == EItemType::ITEM_Equip) // 습득한 아이템이 장비 아이템이라면
		{
			InventoryData.Add(EquipmentItemGenerator(), FLostArcItemData());
		}
		else // 중첩이 가능한 소모형 아이템이라면 
		{
			FoundItem->AddItemCount(ItemCount, ItemData->GetMaxCount()); // 추가되려는 아이템 데이터를 인벤토리에 있는 데이터로 덮어씀
			UE_LOG(LogTemp, Warning, TEXT("This Item Count Now %d"), FoundItem->ItemCount);
		}
	}
	else // 인벤토리에 같은 아이템이 없으면
	{
		UE_LOG(LogTemp, Warning, TEXT("Added Item %d"), ItemCount);
		InventoryData.Add(ItemData, FLostArcItemData(ItemCount)); // 인벤토리에 새로 추가
	}
}

ULostArcItemBase* ULostArcInventoryComponent::EquipmentItemGenerator()
{
	return NewObject<ULostArcItemBase>(this); // 어차피 TMap은 ULostArcItemBase를 받으니 <그대로> 생성해주면 된다.
}
