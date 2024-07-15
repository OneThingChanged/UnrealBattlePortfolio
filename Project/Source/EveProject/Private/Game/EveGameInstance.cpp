// CopyRight Jin


#include "Game/EveGameInstance.h"

#include "..\..\Public\Data\FEnemyDataTable.h"
#include "Data/FImageDataTable.h"

UEveGameInstance::UEveGameInstance()
{
}

void UEveGameInstance::CustomInit()
{
	// for (int32 EnumIndex = static_cast<int32>(ESkillType::None) + 1; EnumIndex < static_cast<int32>(ESkillType::Max); EnumIndex++)
	// {
	// 	ESkillType EnumValue = static_cast<ESkillType>(EnumIndex);
	// 	
	// 	// 값이 있는 경우만 SkillType에 추가
	// 	if (UEnum::GetValueAsString(EnumValue) != "None")
	// 	{
	// 		JinSkillType.Add(EnumValue);
	// 	}
	// }
	//
	// for (int32 EnumIndex = static_cast<int32>(EEveUnitType::None) + 1; EnumIndex < static_cast<int32>(EEveUnitType::Max); EnumIndex++)
	// {
	// 	EEveUnitType EnumValue = static_cast<EEveUnitType>(EnumIndex);
	// 	
	// 	// 값이 있는 경우만 UnitType 추가
	// 	if (UEnum::GetValueAsString(EnumValue) != "None")
	// 	{
	// 		JinUnitType.Add(EnumValue);
	// 	}
	// }
	// // TMap에 추가된 값 확인
	// for (const EEveUnitType TempUnit : JinUnitType)
	// {
	// 	auto ID = static_cast<int32>(TempUnit);
	// 	auto name = FString::FromInt(ID);
	//
	// 	// //캐릭터셋팅
	// 	// FCharacterTable* TempCharacterData = GetCharacterTable(name);
	// 	// if (TempCharacterData != nullptr)
	// 	// {
	// 	// 	CharacterData.Add(TempUnit, TempCharacterData);
	// 	// }
	// 	// else
	// 	// {
	// 	// 	UE_LOG(LogTemp, Error,
	// 	// 		TEXT("Unit Type: %s의 FCharacterTable은 존재하지않습니다."),
	// 	// 		*UEnum::GetValueAsString(TempUnit))
	// 	// 	continue;
	// 	// }
	// 	
	// 	//스탯 세팅
	// 	FCharacterStatTable* TempStatData = GetCharacterStatTable(TempUnit);
	// 	if (TempStatData != nullptr)
	// 	{
	// 		StatData.Add(TempUnit, TempStatData);
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Error,
	// 			TEXT("Unit Type: %s의 FCharacterStatTable은 존재하지않습니다."),
	// 			*UEnum::GetValueAsString(TempUnit))
	// 		continue;
	// 	}
	// 	
	// 	//스킬 세팅
	// 	if (!SkillData.Contains(TempUnit))
	// 	{
	// 		TMap<ESkillType, FCharacterSkillTable*> TempSkillTmap = TMap<ESkillType, FCharacterSkillTable*>();
	// 		SkillData.Add(TempUnit, TempSkillTmap);
	// 	}
	// 	for (const auto& TempSkill : JinSkillType)
	// 	{
	// 		FCharacterSkillTable* TempSkillData = GetCharacterSkillTable(TempUnit, TempSkill);
	// 		if (TempSkillData == nullptr)
	// 		{
	// 			UE_LOG(LogTemp, Warning,
	// 				TEXT("Unit Type: %s의 Skill Type: %s은 존재하지않습니다."),
	// 				*UEnum::GetValueAsString(TempUnit),
	// 				*UEnum::GetValueAsString(TempSkill))
	// 			continue;
	// 		}
	// 		SkillData[TempUnit].Add(TempSkill, TempSkillData);
	// 	}
	// }
	//
	// for (const auto& Pair1 : SkillData)
	// {
	// 	
	// 	for (const auto& Pair2 : Pair1.Value)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("Unit Type: %s, Skill Type: %s"),
	// 			*UEnum::GetValueAsString(Pair2.Value->UnitType),
	// 			*UEnum::GetValueAsString(Pair2.Value->SkillType));
	// 	}
	// }
	SetImageData();
	SetCharacterData();
	SetCharacterStatData();
	SetSkillData();
	SetEnemyData();
}

FCharacterSkillTable* UEveGameInstance::GetCharacterSkillTable(EEveUnitType UnitType, ESkillType SkillType)
{
	auto ID = ((int32)UnitType * 1000) + ((int32)SkillType);
	// auto name = FName(*UEnum::GetValueAsString(ID));
	auto name = FString::FromInt(ID);
	if (auto DataTable = CharacterSkillTable->FindRow<FCharacterSkillTable>(*name,TEXT("")))
	{
		return DataTable;
	}

	return nullptr;
}

FCharacterTable* UEveGameInstance::GetCharacterTable(FString name)
{
	if (auto DataTable = CharacterTable->FindRow<FCharacterTable>(*name,TEXT("")))
	{
		return DataTable;
	}
	return nullptr;
}

FCharacterSkillTable* UEveGameInstance::GetSkillInfo(EEveUnitType UnitType, ESkillType SkillType, int32 Index)
{
	if (SkillData.Contains(UnitType)
		&& SkillData[UnitType].Contains(SkillType)
		&& SkillData[UnitType][SkillType]->SkillIndexInfos.Num() > Index)
	{
		return SkillData[UnitType][SkillType];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Skill Data, [UnitType: %s, SkillType: %s, Index: %d"),
			*UEnum::GetValueAsString(UnitType),
			*UEnum::GetValueAsString(SkillType),
			Index);
	}
	return nullptr;
}

FCharacterSkillTable* UEveGameInstance::GetSkillInfo(EEveUnitType UnitType, ESkillType SkillType)
{
	if (SkillData.Contains(UnitType)
		&& SkillData[UnitType].Contains(SkillType))
	{
		return SkillData[UnitType][SkillType];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Skill Data, [UnitType: %s, SkillType: %s"),
			*UEnum::GetValueAsString(UnitType),
			*UEnum::GetValueAsString(SkillType));
	}
	return nullptr;
}


FCharacterStatTable* UEveGameInstance::GetStatInfo(EEveUnitType UnitType)
{
	if (StatData.Contains(UnitType))
	{
		return StatData[UnitType];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Stat Data, [UnitType: %s]"),
			*UEnum::GetValueAsString(UnitType));
	}
	return nullptr;
}

FCharacterTable* UEveGameInstance::GetCharacterInfo(EEveUnitType UnitType)
{
	if (CharacterData.Contains(UnitType))
	{
		return CharacterData[UnitType];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Stat Data, [UnitType: %s]"),
			*UEnum::GetValueAsString(UnitType));
	}
	return nullptr;
}

FEnemyDataTable* UEveGameInstance::GetEnemyInfo(FName Id)
{
	if (EnemyData.Contains(Id))
	{
		return EnemyData[Id];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Enemy Data, [ID: %s]"),
			Id);
	}
	return nullptr;
}

void UEveGameInstance::Init()
{
	Super::Init();
	CustomInit();
}

void UEveGameInstance::SetCharacterStatData()
{
	if (!IsValid(CharacterStatsTable))
	{
		return;
	}
	// DataTable의 모든 행을 가져와서 처리
	TArray<FCharacterStatTable*> DataRows;
	CharacterStatsTable->GetAllRows<FCharacterStatTable>(TEXT("GetAllRows"), DataRows);
	for (FCharacterStatTable* DataRow : DataRows)
	{
		// TMap에 추가
		StatData.Add(DataRow->UnitType, DataRow);
	}
}

void UEveGameInstance::SetCharacterData()
{
	if (!IsValid(CharacterTable))
	{
		return;
	}
	// DataTable의 모든 행을 가져와서 처리
	TArray<FCharacterTable*> DataRows;
	CharacterTable->GetAllRows<FCharacterTable>(TEXT("GetAllRows"), DataRows);
	for (FCharacterTable* DataRow : DataRows)
	{
		// TMap에 추가
		CharacterData.Add(DataRow->UnitType, DataRow);
	}
}

void UEveGameInstance::SetEnemyData()
{
	if (!IsValid(EnemyTable))
	{
		return;
	}
	// DataTable의 모든 행을 가져와서 처리
	TArray<FEnemyDataTable*> DataRows;
	EnemyTable->GetAllRows<FEnemyDataTable>(TEXT("GetAllRows"), DataRows);
	for (FEnemyDataTable* DataRow : DataRows)
	{
		// TMap에 추가
		EnemyData.Add(DataRow->ID, DataRow);
	}
}

void UEveGameInstance::SetSkillData()
{
	if (!IsValid(CharacterSkillTable))
	{
		return;
	}
	// DataTable의 모든 행을 가져와서 처리
	TArray<FCharacterSkillTable*> DataRows;
	CharacterSkillTable->GetAllRows<FCharacterSkillTable>(TEXT("GetAllRows"), DataRows);
	for (FCharacterSkillTable* DataRow : DataRows)
	{
		// TMap에 추가
		if (!SkillData.Contains(DataRow->UnitType))
		{
			TMap<ESkillType, FCharacterSkillTable*> temp;
			SkillData.Add(DataRow->UnitType, temp);
		}
		SkillData[DataRow->UnitType].Add(DataRow->SkillType, DataRow);
	}
}
UTexture2D* UEveGameInstance::GetImageFromCombatType(EEveCombatType CombatType)
{
	switch (CombatType)
	{
	case EEveCombatType::Fire:
		return ImageData[FName("CombatType_Fire")];
	case EEveCombatType::Wind:
		return ImageData[FName("CombatType_Wind")];
	case EEveCombatType::Lighting:
		return ImageData[FName("CombatType_Lighting")];
	case EEveCombatType::Water:
		return ImageData[FName("CombatType_Water")];
	case EEveCombatType::Physical:
		return ImageData[FName("CombatType_Physical")];
	case EEveCombatType::Imaginary:
		return ImageData[FName("CombatType_Imaginary")];
	}
	return nullptr;
}

void UEveGameInstance::SetImageData()
{
	if (!IsValid(ImageTable))
	{
		return;
	}
	// DataTable의 모든 행을 가져와서 처리
	TArray<FImageDataTable*> DataRows;
	ImageTable->GetAllRows<FImageDataTable>(TEXT("GetAllRows"), DataRows);
	for (FImageDataTable* DataRow : DataRows)
	{
		// TMap에 추가
		ImageData.Add(DataRow->ID, DataRow->Image);
	}
}

FCharacterStatTable* UEveGameInstance::GetCharacterStatTable(EEveUnitType UnitType)
{
	auto ID = (int32)UnitType;

	auto name = FString::FromInt(ID);
	if (auto DataTable = CharacterStatsTable->FindRow<FCharacterStatTable>(*name,TEXT("")))
	{
		return DataTable;
	}
	return nullptr;
}

float UEveGameInstance::GetDamageMultiplier(EEveUnitType UnitType, ESkillType SkillType, int32 Index)
{
	if (SkillData.Contains(UnitType)
		|| SkillData[UnitType].Contains(SkillType)
		|| SkillData[UnitType][SkillType]->SkillIndexInfos.Num() > Index)
	{
		return SkillData[UnitType][SkillType]->SkillIndexInfos[Index].DamageMultiplier;
	}
	return 0;
}