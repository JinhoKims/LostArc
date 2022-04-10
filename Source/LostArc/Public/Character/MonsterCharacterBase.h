// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/AIAbilityComponent.h"
#include "GameFramework/Character.h"
#include "MonsterCharacterBase.generated.h"

UCLASS(Blueprintable)
class LOSTARC_API AMonsterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterCharacterBase();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	class UMonsterBaseAnimInstance* GetMonsterAnim() { return MonsterAnim; }
	class UAIAbilityComponent* GetAbilityComponent() { return AbilityComponent; }
	float GetBasicAttackRange() { return AbilityComponent->GetBasicAttackRange(); }

	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MonsterHP;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MonsterSpeed;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float BasicAttackRange;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UMonsterBaseAnimInstance* MonsterAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = true))
	class UAIAbilityComponent* AbilityComponent;
};
