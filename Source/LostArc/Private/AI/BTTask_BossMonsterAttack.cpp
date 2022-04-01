// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_BossMonsterAttack.h"
#include "Abilities/AI/AISkillBase.h"
#include "Controller/BossMonsterAIController.h"
#include "AnimInstances/BossMonsterAnimInstance.h"
#include "Character/BossMonsterCharacter.h"
#include "Component/AIAbilityComponent.h"

UBTTask_BossMonsterAttack::UBTTask_BossMonsterAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_BossMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto MonsterCharacter = Cast<ABossMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (MonsterCharacter == nullptr) return EBTNodeResult::Failed;
	UE_LOG(LogTemp,Warning,TEXT("Effects"));
	
	auto MonsterAnim = Cast<UBossMonsterAnimInstance>(MonsterCharacter->GetMesh()->GetAnimInstance());
	if (MonsterAnim->Montage_IsPlaying(MonsterAnim->MonsterFlinchMontage) || (MonsterAnim->Montage_IsPlaying(MonsterAnim->MonsterDeathMontage))) return EBTNodeResult::Failed;

	auto AbilityComp = MonsterCharacter->GetAbilityComponent();
	if(AbilityComp->GetCDProperty())
	{
		AbilityComp->AIAbilityCast(MonsterCharacter, EAbilityType::MeleeSkill_1);

		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::Failed;
}

void UBTTask_BossMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(!UAISkillBase::bAnimationRunning)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); 
	}
}
