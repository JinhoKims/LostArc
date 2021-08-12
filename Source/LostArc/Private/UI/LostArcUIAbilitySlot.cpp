// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIAbilitySlot.h"
#include "Components/Image.h"

void ULostArcUIAbilitySlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (ThumbTexture2D->IsValidLowLevel())
	{
		Image_Thumb->SetBrushFromTexture(ThumbTexture2D);
	}
}
