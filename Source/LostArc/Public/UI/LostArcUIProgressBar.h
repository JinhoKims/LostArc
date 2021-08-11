// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUIProgressBar.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EBarType
{
	HP UMETA(DisplayName = "HP"),
	MP UMETA(DisplayName = "MP"),
	EXP UMETA(DisplayName = "EXP")
};


UCLASS()
class LOSTARC_API ULostArcUIProgressBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void Init(EBarType type, class ALostArcCharacter *Character);
	void UpdateProgressBar();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ProgressBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurrentText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MaxText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBarType> ThisBarType;
};
