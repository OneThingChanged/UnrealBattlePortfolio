// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FCharacterSkillTable.h"
#include "Data/FCharacterStatTable.h"
#include "Data/FCharacterTable.h"
#include "Engine/GameInstance.h"
#include "Eve/Define.h"
#include "EveGameInstance.generated.h"

struct FEnemyDataTable;

UCLASS()
class EVEPROJECT_API UEveGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	TMap<EEveUnitType, FCharacterTable*> CharacterData;
	TMap<EEveUnitType, FCharacterStatTable*> StatData;
	TMap<EEveUnitType, TMap<ESkillType, FCharacterSkillTable*>> SkillData;
	TMap<FName, FEnemyDataTable*> EnemyData;

	UPROPERTY(EditAnywhere, Category = "State")
	TArray<ECharState> CheckAbleToInputState;
	UPROPERTY(EditAnywhere, Category = "State")
	TArray<ECharState> CheckAbleToInputNormalAttack;
	UPROPERTY(EditAnywhere, Category = "State")
	TArray<ECharState> CheckAbleToMove;
	UPROPERTY(EditAnywhere, Category = "State")
	TArray<ECharState> CheckAbleToHit;
	
	//DataManager
	TMap<FName, UTexture2D*> ImageData;
	UTexture2D* GetImageFromCombatType(EEveCombatType CombatType);
	
	// TArray<EEveUnitType> JinUnitType;
	// TArray<ESkillType> JinSkillType;
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterSkillTable;
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterStatsTable;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterTable;

	UPROPERTY(EditAnywhere)
	UDataTable* EnemyTable;
	
	UPROPERTY(EditAnywhere)
	UDataTable* ImageTable;
private:
	FCharacterStatTable* GetCharacterStatTable(EEveUnitType UnitType);
	FCharacterSkillTable* GetCharacterSkillTable(EEveUnitType UnitType, ESkillType SkillType);
	FCharacterTable* GetCharacterTable(FString name);
	void SetCharacterData();
	void SetCharacterStatData();
	void SetEnemyData();
	void SetSkillData();
	void SetImageData();
public:
	UEveGameInstance();
	
	
	FCharacterSkillTable* GetSkillInfo(EEveUnitType UnitType, ESkillType SkillType, int32 Index);
	FCharacterSkillTable* GetSkillInfo(EEveUnitType UnitType, ESkillType SkillType);
	FCharacterStatTable* GetStatInfo(EEveUnitType UnitType);
	FCharacterTable* GetCharacterInfo(EEveUnitType UnitType);
	FEnemyDataTable* GetEnemyInfo(FName Id);
public:
	virtual void Init() override;



	void CustomInit();
	float GetDamageMultiplier(EEveUnitType UnitType, ESkillType SkillType, int32 Index);
};


