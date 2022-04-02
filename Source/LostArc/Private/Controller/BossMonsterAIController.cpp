// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/BossMonsterAIController.h"

ABossMonsterAIController::ABossMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/Boss/BB_Boss.BB_Boss'")); // 블루프린트의 블랙보드와 연동
	if (BBObject.Succeeded()) { BBAsset = BBObject.Object; }

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/Boss/BT_Boss.BT_Boss'")); // BP의 BT와 연동
	if (BTObject.Succeeded()) { BTAsset = BTObject.Object; }
}