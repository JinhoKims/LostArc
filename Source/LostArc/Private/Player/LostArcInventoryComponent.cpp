// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LostArcInventoryComponent.h"
#include "Items/LostArcItemBase.h"
#include "UI/LostArcUIInventory.h"
#include "UI/LostArcUIInventorySlot.h"
#include "UI/LostArcUIMainHUD.h"
#include "Controller/LostArcPlayerController.h"
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

	InventorySlot.SetNum(16); // InvenSlot을 Null로 초기화 

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
	AddPickupItem(DataTable.Find("Potion_Health"), 15);

	UE_LOG(LogTemp, Warning, TEXT("======================="));
	
	AddPickupItem(DataTable.Find("Potion_Mana"), 10);
	AddPickupItem(DataTable.Find("Potion_Mana"), 17);
	AddPickupItem(DataTable.Find("Potion_Mana"), 10);
	
	UE_LOG(LogTemp, Warning, TEXT("======================="));
	
	AddPickupItem(DataTable.Find("Potion_Health"), 10);
	AddPickupItem(DataTable.Find("Potion_Mana"), 10);

	UE_LOG(LogTemp, Warning, TEXT("======================="));

	auto Character = Cast<ALostArcCharacter>(GetOwner());
	auto Controller = Cast<ALostArcPlayerController>(Character->GetController());

	auto Data = InventoryData.Find(Controller->MainHUD->BP_Inventory->InventorySlots[0]->Item);
	if (Data)
		UE_LOG(LogTemp, Warning, TEXT("Health Item Count is : %d"), Data->ItemCount);
	
	Data = InventoryData.Find(Controller->MainHUD->BP_Inventory->InventorySlots[1]->Item);
	if (Data)
		UE_LOG(LogTemp, Warning, TEXT("Mana Item Count is : %d"), Data->ItemCount);
		

	
	if (InventorySlot[12] == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("This isF NullptrS!"));
	}
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

	FLostArcItemData* FoundItem = InventoryData.Find(*NewItem); // 인벤토리 서치 (없으면 Null을 반환함)
	auto ItemData = *NewItem;

	auto Character = Cast<ALostArcCharacter>(GetOwner());
	auto Controller = Cast<ALostArcPlayerController>(Character->GetController());

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

		for (int i = 0; i < 16; i++)
		{
			if (Controller->MainHUD->BP_Inventory->InventorySlots[i]->Item == nullptr)
			{
				Controller->MainHUD->BP_Inventory->InventorySlots[i]->Item = *NewItem;
				break;
			} 
		}
	}
}

ULostArcItemBase* ULostArcInventoryComponent::EquipmentItemGenerator()
{
	return NewObject<ULostArcItemBase>(this);
	// 수정 필요 NewItem 객체의 클래스형을 리턴해줘야 한다.
}
