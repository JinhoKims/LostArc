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
		ItemData.Add(DataTable.FindRef(ItemClass[i].GetDefaultObject()->ItemName)); // pickup 함수에서 아이템을 추가하는 코드다. 지금은 테스트용으로 해놨다.
	}


	//for (auto& Elem : DataTable)
	//{
	//	Elem.Key = ItemClass[i].GetDefaultObject()->ItemName;
	//	Elem.Value = NewObject<ULostArcItemBase>(this, ItemClass[i++].Get());
	//}
}

// Called when the game starts
void ULostArcInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ItemData.Find(DataTable.FindRef("Potion_Mana")))
	{
		UE_LOG(LogTemp, Warning, TEXT("AI"));
	}

	
}

// Called every frame
void ULostArcInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void ULostArcInventoryComponent::AddPickupItem(ULostArcItemBase* NewItem, int32 ItemCount)
{
	FLostArcItemData OldData;
	GetInventoryData(NewItem, OldData);

	FLostArcItemData NewData = OldData;
	NewData.UpdateItemData(FLostArcItemData(ItemCount), NewItem->MaxCount);
}


bool ULostArcInventoryComponent::GetInventoryData(ULostArcItemBase* Item, FLostArcItemData& ItemDatavs) const
{
	const FLostArcItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		ItemDatavs = *FoundItem;
		return true;
	}
	// Create new ItemData at Inventory
	ItemDatavs = FLostArcItemData(0);
	return false;
}