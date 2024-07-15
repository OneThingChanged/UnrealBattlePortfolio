// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EveAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UEveAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEveAnimInstance();
	void SetPlayRate(AActor* Actor, float Speed, float DelayTime);
	void temp();
private:
	float PlayRate = 1;
	FTimerHandle TimerHandle;
};
