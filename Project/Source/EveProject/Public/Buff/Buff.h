// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Buff.generated.h"

/**
 * 
 */

enum UBuffProp : uint8 
{
	None = 0,
	Buff = 1 << 0,
	Debuff = 1 << 1,
	State = 1 << 2,
};

USTRUCT()
struct FBuffInitParam
{
	GENERATED_BODY()

	float Duration = 0.f;
};

UCLASS()
class UBuff : public UObject
{
	GENERATED_BODY()
	
protected:
	virtual void OnBuffStart() {};
	virtual void OnBuffEnd() {};

public:
	virtual void Init(FBuffInitParam* Param);
	virtual void Start();
	virtual void Stop();

	float GetExperationTime() const;
	float GetRemainTime() const;

public:
	FSimpleDelegate OnBuffStartDelegate;
	FSimpleDelegate OnBuffEndDelegate;

protected:
	UBuffProp Prop = UBuffProp::None;
	float Duration = 0.f;

	bool bActivate = false;
	float ExpirationServerTime = 0.f;

};
