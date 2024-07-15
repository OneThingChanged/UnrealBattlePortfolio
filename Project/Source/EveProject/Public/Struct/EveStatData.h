#pragma once

#include "CoreMinimal.h"
#include "Eve/Define.h"
#include "EveStatData.generated.h"

class EVEPROJECT_API EveStatInfo
{
public:
	EveStatInfo();
	~EveStatInfo();
};

USTRUCT(Atomic,BlueprintType)
struct FSkillIndexInfo
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float DamageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float CombatPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int HitValue;	
};

USTRUCT(Atomic,BlueprintType)
struct FEveStatData
{
	GENERATED_USTRUCT_BODY()

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	EEveStatType StatType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float DefaultValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	bool UseRegen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float RegenValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float RegenTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float DelayValue;



	FEveStatData()
		: CurValue(100.0f),
	UseRegen(false),
	RegenValue(0.0f),
	RegenTime(0.1f),
	DelayValue(0.0f)
	{
		
	}
};

USTRUCT(Atomic,BlueprintType)
struct FEveSkillData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float SkillMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float CoolTime = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float Resource = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	bool useMoveCurve = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	UCurveFloat* moveCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	UAnimMontage* skillMontage;

	FEveSkillData()
		: SkillMultiplier(1.0f)
	{
	}
};

