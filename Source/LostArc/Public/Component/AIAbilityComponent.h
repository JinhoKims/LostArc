// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AI/AISkillBase.h"
#include "Components/ActorComponent.h"
#include "AIAbilityComponent.generated.h"

enum EAbilityType;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOSTARC_API UAIAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAIAbilityComponent();
	void BasicAttack(class ABossMonsterCharacter* Monster);

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UAISkillBase>> AbilityClass;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TArray<UAISkillBase*> Abilities;
};
