// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUIInven.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcUIInven : public UUserWidget
{
	GENERATED_BODY()

public:
	void ConstructSlot(int32 Index, bool Flag);
	
protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true))
	TArray<class ULostArcUIInvenSlot*> InvenSlot;

	class ALostArcCharacter* OwnerCharacter;
};
