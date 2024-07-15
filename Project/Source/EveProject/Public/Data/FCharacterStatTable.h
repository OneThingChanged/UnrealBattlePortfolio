#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Eve/Define.h"
#include "..\Struct\EveStatData.h"
#include "FCharacterStatTable.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStatTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	EEveUnitType UnitType = EEveUnitType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TArray<FEveStatData> Stats;
};
