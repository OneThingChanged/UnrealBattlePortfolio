#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Eve/Define.h"
#include "Struct/EveStatData.h"
#include "FCharacterSkillTable.generated.h"

USTRUCT(BlueprintType)
struct FCharacterSkillTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	EEveUnitType UnitType = EEveUnitType::None;
	
	UPROPERTY(EditAnywhere, Category = "Skill")
	ESkillType SkillType = ESkillType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	EDamageAreaType SkillAreaType = EDamageAreaType::Area;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	UTexture2D* ImageIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float CoolTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float Radius = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float Degree = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float Resource = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	bool UseMoveCurve = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float MoveMultiplier;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	UCurveFloat* MoveCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	UAnimMontage* SkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float HitRecoveryTime = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float HitDelaySpeed = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TArray<FSkillIndexInfo> SkillIndexInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TSubclassOf<UCameraShakeBase> CameraShake;
};