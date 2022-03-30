// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterCharacterBase.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class LOSTARC_API AMonsterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	FOnAttackEndDelegate OnAttackEnd;
	
	AMonsterCharacterBase();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void MonsterAttack();
	virtual void MonsterAttackHitCheck();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	float GetMonsterAttackRange() { return AttackRange; }

protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MonsterHP;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AttackRange;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AttackRadius;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MonsterSpeed;

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UMonsterBaseAnimInstance* MonsterAnim;
};
