// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LostArcCharacterAbilityBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCDDelegate, bool);

UCLASS()
class LOSTARC_API ULostArcCharacterAbilityBase : public UObject
{
	GENERATED_BODY()
	
public:	
	virtual void ConstructAbility(float mana, float cooldown, float factor);
	virtual void Use(class ALostArcCharacter* Character);
	virtual void HitCheck(class ALostArcCharacter* Character);
	virtual bool AbilityStatusCheck(class ALostArcCharacter* Character);
	void CharacterRotatetoCursor(class ALostArcCharacter* Character);

public:
	UPROPERTY()
	float CoolDown;

	UPROPERTY()
	float ManaCost;

	UPROPERTY()
	float Damage_Factor;

	bool bAbilityNowAvailable; // 삭제 : Use 함수를 bool 반환형으로 전환하고 if(AbilityStatusCheck(Character)) { ... return true; }로 교체 
	bool bAbilityNowCD; // 삭제 : GetWorldTimerManager().IsTimerActive(AbilityCoolDownTimer)로 교체

	static bool bAnimationRunning;
	FTimerHandle AbilityCoolDownTimer;  // 변수명 AbilityCDTimer로 바꾸기

	FOnAbilityCDDelegate OnAbilityhasCD; // 변수명 AbilityCDDelegate로 바꾸기

	// 둘을 합치는걸 추천
	TPair<FTimerHandle, FOnAbilityCDDelegate> AbilityCDProperty;

protected:
	TPair<FCollisionQueryParams, TArray<FHitResult>> HitResultProperty;
};
