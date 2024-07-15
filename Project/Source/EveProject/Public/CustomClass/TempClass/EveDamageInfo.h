// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EveDamageInfo.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UEveDamageInfo : public UObject
{
	GENERATED_BODY()
public:

	UEveDamageInfo();
	int Damage;
	int CombatGauge;
};
