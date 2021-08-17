// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LostArcInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct LOSTARC_API FLostArcItemData
{
	GENERATED_BODY()

	FLostArcItemData() :ItemCount(1) {}
	FLostArcItemData(int32 Count):ItemCount(Count) {}

	int32 ItemCount;

	void UpdateItemData(const FLostArcItemData& Other, int32 MaxCount)
	{
		if (MaxCount <= 0)
		{
			MaxCount = 100000;
		}
		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount); // 아이템 수량 증가 (아이템 최대 수량이 1일 경우 수량이 증가하지 않음)
	}


	bool IsValid() const
	{
		return ItemCount > 0; // 아이템을 사용할 때 슬롯에 더 이상 수량이 존재하지 않으면 완전히 삭제하기 위한 함수다
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARC_API ULostArcInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULostArcInventoryComponent();
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	TMap<class ULostArcItemBase*, FLostArcItemData> InventoryData;
	TMap<class ULostArcItemBase*, int32> TestData;
	void AddPickupItem(class ULostArcItemBase* NewItem, int32 ItemCount);
	bool GetInventoryData(class ULostArcItemBase* Item, FLostArcItemData& ItemData) const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<ULostArcItemBase>> ItemClass;

	UPROPERTY(meta = (AllowPrivateAccess = true))
	TMap<FString, class ULostArcItemBase*> DataTable;

	UPROPERTY(meta = (AllowPrivateAccess = true))
	TMap<class ULostArcItemBase*, int32> ItemData;

	/* 
		TMap의 ItemData는 Value (수량)역할을 하며 Item 은 Key 역할을 해서 인벤토리에 해당 아이템이 들어있는지 확인한다.
		아이템을 획득했을 때 다음과 같이 실행된다.	
	
	   1. InventoryData.Find(Item)으로 TMap에 같은 아이템이 있는지 찾는다. 
	   
	   2.1 아이템이 이미 있고 MaxCount가 무한대면 해당 인덱스에 아이템 카운트를 더한다.
	   2.2 아이템이 이미 있고 MaxCount가 1이면 장비 아이템이라는 뜻이니 TMap을 새로 Add 한다.

	   3.1 아이템이 없으면 TMap을 해당 아이템으로 Add 하고 아이템 카운트를 추가한다.

	   아이템을 사용할 땐 ItemCount 를 감소해주고 IsValid()를 호출해준다.


	  ItemBase 기반의 모든 파생형 객체를 미리 동적 할당하여 생성해준다.
	  AddPickupItem()이 호출될 때 이 객체의 포인터를 넘겨준다.
	  그러면 Find() 함수가 명확하게 주소 파악이 되어 제대로 작동된다.
	*/



};
