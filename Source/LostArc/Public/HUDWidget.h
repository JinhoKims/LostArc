// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class ULostArcCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
	void UpdateMPWidget();

private:
	TWeakObjectPtr<class ULostArcCharacterStatComponent> CurrentCharacterStat;
	
	UPROPERTY()
	TArray<class UBorder*> SkillSlots;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

	UPROPERTY()
	class UProgressBar* MPProgressBar;
};
