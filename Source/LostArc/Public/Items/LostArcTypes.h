// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LostArcTypes.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcTypes : public UObject
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct LOSTARC_API FLostArcItemData
{
	GENERATED_BODY()
	
	int32 ItemCount;

	FLostArcItemData() :ItemCount(1) {}
	FLostArcItemData(int32 Count) :ItemCount(Count) {}

	void AddItemCount(int32 AddCount, int32 MaxCount)
	{
		if (MaxCount <= 0) // 이 아이템 데이터의 MaxCount가 무한대면
		{
			MaxCount = 100000;
		}
		ItemCount = FMath::Clamp(ItemCount + AddCount, 0, MaxCount); // Count를 증가 (아이템 최대 수량이 1일 경우 수량
	}

	bool IsValid() const
	{
		return ItemCount > 0; // 아이템을 사용할 때 슬롯에 더 이상 수량이 존재하지 않으면 완전히 삭제하기 위한 함수다
	}
};