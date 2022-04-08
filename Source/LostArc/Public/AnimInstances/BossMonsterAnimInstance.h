// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MonsterBaseAnimInstance.h"
#include "BossMonsterAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonsterEffectCheckDelegate, EAbilityType, Type);

UCLASS(Blueprintable)
class LOSTARC_API UBossMonsterAnimInstance : public UMonsterBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	TArray<UAnimMontage*> BossBasicAttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* BossSkill_1_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* BossSkill_2_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* BossSkill_3_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* BossSkill_4_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	UAnimMontage* Overdrive_Montage;
	
	UBossMonsterAnimInstance();
	virtual void PlayAttackMontage() override;
	TArray<UAnimMontage*> GetBossBasicAttackMontages();
	int32 GetBasicAttackStep();

	UFUNCTION()
	void AnimNotify_MonsterJumpCheck();

private:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	FOnMonsterEffectCheckDelegate OnMonsterEffectCheckDelegate;
};
