// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff/Buff.h"
#include "CombatBuff.generated.h"

USTRUCT()
struct FIncreassDamageInitParam : public FBuffInitParam
{
	GENERATED_BODY()

	float BaseDamageIncrease = 0.f;
};

UCLASS()
class UIncreaseDamage : public UBuff
{
	GENERATED_BODY()
	
public:
	UIncreaseDamage();
	virtual void Init(FBuffInitParam* Param) override;

protected:
	virtual void OnBuffStart() override;
	virtual void OnBuffEnd() override;

private:
	float BaseDamageIncrease = 0.f;

};

USTRUCT()
struct FCreateShieldInitParam : public FBuffInitParam
{
	GENERATED_BODY()

	int32 Shield = 0.f;
};

UCLASS()
class UCreateShield : public UBuff
{
	GENERATED_BODY()
	
public:
	UCreateShield();
	virtual void Init(FBuffInitParam* Param) override;

protected:
	virtual void OnBuffStart() override;
	virtual void OnBuffEnd() override;

private:
	int32 Shield = 0;
	int32 RemainShield = 0;
};

USTRUCT()
struct FDecreaseComboInitParam : public FBuffInitParam
{
	GENERATED_BODY()

	int32 DecreaseCombo = 0.f;
};

UCLASS()
class UDecreaseCombo : public UBuff
{
	GENERATED_BODY()
	
public:
	UDecreaseCombo();
	virtual void Init(FBuffInitParam* Param) override;

protected:
	virtual void OnBuffStart() override;
	virtual void OnBuffEnd() override;

private:
	int32 DecreaseCombo = 0;
};

USTRUCT()
struct FGroggyTimeInitParam : public FBuffInitParam
{
	GENERATED_BODY()

	float GroggyTime = 0.f;
};

UCLASS()
class UGroggyState : public UBuff
{
	GENERATED_BODY()
	
public:
	UGroggyState();
	virtual void Init(FBuffInitParam* Param) override;

protected:
	virtual void OnBuffStart() override;
	virtual void OnBuffEnd() override;
};