// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Eve/Define.h"
#include "UObject/Object.h"
#include "EveStatInfo.generated.h"

struct FEnemyDataTable;
struct FCharacterStatTable;
/**
 * 
 */
UCLASS()
class EVEPROJECT_API UEveStatInfo : public UObject
{
	GENERATED_BODY()
public:
	void Init(FEnemyDataTable* Data);
	void Init(FCharacterStatTable* Data);
	
public:
	UPROPERTY(EditAnywhere, Category=Current)
	int Hp;
	UPROPERTY(EditAnywhere, Category=Current)
	int Damage;
	UPROPERTY(EditAnywhere, Category=Current)
	int Armor;
	UPROPERTY(EditAnywhere, Category=Current)
	int CombatGauge;
	UPROPERTY(EditAnywhere, Category=Current)
	int HitRecovery;
	UPROPERTY(EditAnywhere, Category=Current)
	int32 Shield;
	
public:
	UPROPERTY(EditAnywhere, Category=Base)
	FName ID;
	UPROPERTY(EditAnywhere, Category=Base)
	int MaxHp;
	UPROPERTY(EditAnywhere, Category=Base)
	int BaseDamage;
	UPROPERTY(EditAnywhere, Category=Base)
	int BaseArmor;
	UPROPERTY(EditAnywhere, Category=Base)
	int BaseHitRecovery;
	UPROPERTY(EditAnywhere, Category=Base)
	int MaxCombatGauge;
	UPROPERTY(EditAnywhere, Category=Base)
	float CombatRecoveryTime;
	UPROPERTY(EditAnywhere, Category=Base)
	TArray<EEveCombatType> CombatTypes;
};
