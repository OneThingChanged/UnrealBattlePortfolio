// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Eve/Define.h"
#include "EveSkillInfo.generated.h"



struct FCharacterSkillTable;
UCLASS()
class EVEPROJECT_API UEveSkillInfo : public UObject
{
	GENERATED_BODY()
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetAbleToUseSkill, UEveSkillInfo*, CurSkillInfo);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillTick, UEveSkillInfo*, CurSkillInfo);
	
	void EveTick(float DeltaTime);
	
	UPROPERTY()
	EEveUnitType UnitType;
	UPROPERTY()
	ESkillType SkillType;
	UPROPERTY()
	float MaxCoolTime;
	UPROPERTY()
	float CurCoolTime;
	UPROPERTY()
	bool AbleToUseSkill = false;
	

	FOnSetAbleToUseSkill FOnSetAbleToUseSkillAction;
	FOnSkillTick FOnSkillTickAction;

	FCharacterSkillTable* Data;
	void SetData(FCharacterSkillTable* SkillInfo);
};
