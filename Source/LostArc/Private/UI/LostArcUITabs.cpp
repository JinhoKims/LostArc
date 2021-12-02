// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUITabs.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/LostArcUISlotDrag.h"

void ULostArcUITabs::SetUITabsFromParent(UUserWidget* Parent, ETabType ParType)
{
	TabType = ParType;
	ParentWidget = Parent;
}

FReply ULostArcUITabs::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
	}
	
	return reply.NativeReply;
}

void ULostArcUITabs::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	ULostArcUISlotDrag* WidgetDD = Cast<ULostArcUISlotDrag>(UWidgetBlueprintLibrary::CreateDragDropOperation(ULostArcUISlotDrag::StaticClass()));
	if (WidgetDD == nullptr) return;

	WidgetDD->SlotType = ESlotType::TitleTab;
	WidgetDD->WidgetToDrag = this; // 드래그할 위젯(this)
	WidgetDD->MouseOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()); // 마우스 Offset
	WidgetDD->DefaultDragVisual = ParentWidget; // 드래그 할 때 보일 위젯(인벤토리 위젯)
	WidgetDD->Pivot = EDragPivot::MouseDown; // MouseDown한 지점을 기준
	OutOperation = WidgetDD; // NativeOnDrop 호출

	UE_LOG(LogTemp,Warning,TEXT("Delete"));
	
	//this->RemoveFromParent();
	//ParentWidget->RemoveFromParent(); // 두개의 위젯이 보이지 않게 하기 위해 부모에서 제거한다.
	
	
	// 하지만 부모에서 제거하면 이동 후 드래그를 끝냈을 때 인벤토리 위젯이 Main_HUD(부모)에서 없어져서 안보이게 된다.
	// 따라서 MainWidget의 NativeOnDrop을 오버라이드 하여 드래그를 놓았을 때 NativeOnDrop을 통해 받아온 Operation으로 MainWidget에 AddToViewport해줌으로써 보여줘야 한다.		
}
