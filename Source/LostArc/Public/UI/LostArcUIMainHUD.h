// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUIMainHUD.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcUIMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class ULostArcUIProgressBar* BP_HPBAR;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class ULostArcUIProgressBar* BP_MPBAR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class ULostArcUIProgressBar* BP_EXPBAR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<class ULostArcUIAbilitySlot*> AbilitySlots;
};
