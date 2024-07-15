// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Eve/Define.h"
#include "UObject/Object.h"
#include "FEnemyDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ID;
	
	UPROPERTY(EditAnywhere)
	int Hp;
	
	UPROPERTY(EditAnywhere)
	int Damage;

	UPROPERTY(EditAnywhere)
	int Armor;

	UPROPERTY(EditAnywhere)
	int HitRecovery;

	UPROPERTY(EditAnywhere)
	int CombatGauge;

	UPROPERTY(EditAnywhere)
	float CombatRecoveryTime;
	
	UPROPERTY(EditAnywhere)
	TArray<EEveCombatType> CombatTypes;
};
