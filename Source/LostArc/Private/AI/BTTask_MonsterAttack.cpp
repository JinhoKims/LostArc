// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_MonsterAttack.h"
#include "Abilities/Skill/AI/AISkillBase.h"
#include "Controller/MonsterBaseAIController.h"
#include "AnimInstances/MonsterBaseAnimInstance.h"
#include "Character/MonsterCharacterBase.h"
#include "Component/AIAbilityComponent.h"

UBTTask_MonsterAttack::UBTTask_MonsterAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto MonsterCharacter = Cast<AMonsterCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (MonsterCharacter == nullptr) return EBTNodeResult::Failed;
	
	auto MonsterAnim = Cast<UMonsterBaseAnimInstance>(MonsterCharacter->GetMesh()->GetAnimInstance());
	if (MonsterAnim->Montage_IsPlaying(MonsterAnim->MonsterFlinchMontage) || (MonsterAnim->Montage_IsPlaying(MonsterAnim->MonsterDeathMontage))) return EBTNodeResult::Failed;
	
	auto AbilityComp = MonsterCharacter->GetAbilityComponent();
	AbilityComp->AIAbilityCast(MonsterCharacter);
	
	return EBTNodeResult::InProgress; // When the task is first run
}

void UBTTask_MonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!UAISkillBase::bAnimationRunning)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // 태스크가 Succeeded를 반환하지 못하면 ExecuteTask에서 InProgress를 반환하여 기다리게한다. bIsAttacking이 false라면 Succeeded를 반환한다.
	}
}

