// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LostArcInventoryComponent.h"
#include "Items/LostArcItemBase.h"
#include "UI/LostArcUIInventory.h"
#include "UI/LostArcUIInventorySlot.h"
#include "Items/LostArcItemPotion_Health.h"
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

	for (int i = 0; i < 10; i++)
	{
		ItemTable.Add(ItemClass[i].GetDefaultObject()->ItemName, ItemClass[i]); // 아이템 테이블에 모든 아이템 정보를 넣는다.
	}

	InventorySlot.SetNum(16); // InvenSlot을 Null로 초기화 
}

// Called when the game starts
void ULostArcInventoryComponent::BeginPlay()
{
	Super::BeginPlay();



	UE_LOG(LogTemp, Warning, TEXT("======================="));
	AddedPickupItem("Potion_Mana", 15);
	AddedPickupItem("Potion_Mana", 21);
	AddedPickupItem("Potion_Mana", 48);
	AddedPickupItem("Potion_Mana", 56);
	UE_LOG(LogTemp, Warning, TEXT("======================="));
	AddedPickupItem("Potion_Health", 10);
	AddedPickupItem("Potion_Health", 64);
	AddedPickupItem("Potion_Health", 88);
	UE_LOG(LogTemp, Warning, TEXT("======================="));
	AddedPickupItem("Potion_Mana", 25);
	AddedPickupItem("Potion_Mana", 678);

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
		if (!ItemData->IsConsumable()) // 습득한 아이템이 장비 아이템이라면
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

		/*for (int i = 0; i < 16; i++)
		{
			if (Controller->MainHUD->BP_Inventory->InventorySlots[i]->Item == nullptr)
			{
				Controller->MainHUD->BP_Inventory->InventorySlots[i]->Item = *NewItem;
				break;
			} 
		}*/
	}
}

void ULostArcInventoryComponent::AddPickupItemds(ULostArcItemBase** NewItem, int32 ItemCount)
{
	if (NewItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewItem is nullptr"));
		return;
	}

	int32* SlotIndex = InventoryDatas.Find(*NewItem);
	auto ItemData = *NewItem;
	
	if (SlotIndex) // 기존에 있는 아이템이라면
	{
		if (!ItemData->IsConsumable())
		{
			// 인벤토리에 장비 아이템 새로 추가
		}
		else // 아이템 카운트 증가
		{
			ItemData->AddItemCount(ItemCount);
		}
	}
	else // 새로운 아이템이라면 
	{
		for (int i = 0; i < 16; i++)
		{
			if (InventorySlot[i] == nullptr)
			{
				InventoryDatas.Add(ItemData, i);
				InventorySlot[i] = ItemData;
				break;
			}
		}
	}

}

void ULostArcInventoryComponent::AddedPickupItem(FString ItemName, int32 ItemCount)
{
	auto NewItem = ItemTable.Find(*ItemName)->GetDefaultObject();

	if (NewItem)
	{
		if (NewItem->IsConsumable()) // 소비 아이템
		{
			if (ConsumableItemCheck(NewItem, ItemCount)) // 소비템이 인벤에 이미있는 경우
			{
				
			}
			else // 소비템을 새로 추가하는 경우
			{
				for (int i = 0; i < 16; i++)
				{
					if (InventorySlot[i] == nullptr)
					{
						InventorySlot[i] = NewObject<ULostArcItemBase>(this, ItemTable.Find(ItemName)->Get());
						UE_LOG(LogTemp, Warning, TEXT("%s Item's Added"), *ItemName);
						break;
					}
				}
			}
		}
		else // 장비 아이템
		{
			
		}
	}
}

bool ULostArcInventoryComponent::ConsumableItemCheck(ULostArcItemBase* NewItem, int32 ItemCount)
{
	for (int i = 0; i < 16; i++)
	{
		if (InventorySlot[i] != nullptr)
		{
			if (InventorySlot[i]->ItemName == NewItem->ItemName) // 같은 아이템이 인벤에 있을 경우
			{
				InventorySlot[i]->AddItemCount(ItemCount);
				UE_LOG(LogTemp, Warning, TEXT("Now Item Count is %d"), InventorySlot[i]->GetItemQuantity());
				return true;
			}
		}
	}
	return false;
}




ULostArcItemBase* ULostArcInventoryComponent::EquipmentItemGenerator()
{
	return NewObject<ULostArcItemBase>(this);
	// 수정 필요 NewItem 객체의 클래스형을 리턴해줘야 한다.
}
