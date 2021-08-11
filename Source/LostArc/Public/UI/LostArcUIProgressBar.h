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


public:
	virtual void NativeConstruct() override;
	void Init(class ALostArcCharacter *Character);
	void UpdateProgressBar(EBarType Type);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ProgressBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurrentText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MaxText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SlashText;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = true))
	TEnumAsByte<EBarType> BarType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = true))
	UTexture2D* BarTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = true))
	FLinearColor BarColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = true))
	FVector2D BarShearValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = true))
	FVector2D BarRenderScale;
};
