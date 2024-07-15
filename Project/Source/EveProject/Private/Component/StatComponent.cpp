// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/StatComponent.h"
#include "Character/EveCombatCharacter.h"
#include "CustomClass/InfoClass/EveStatInfo.h"
#include "CustomClass/TempClass/EveDamageInfo.h"
#include "Game/EveGameInstance.h"

struct FCharacterStatTable;
// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatComponent::SetCalculateCombatGauge(bool onOff)
{
	IsCalculateCombatGauge = onOff;
}

void UStatComponent::Init(AEveCombatCharacter* EveCombatCharacter)
{
	CustomOwner = EveCombatCharacter;
	EEveUnitType TempUnitType = CustomOwner->GetUnitType();


	EEveSideType TempSideType = CustomOwner->GetSideType();
	UEveGameInstance* GameInstance = Cast<UEveGameInstance>(GetOwner()->GetGameInstance());
	switch (TempSideType)
	{
	case EEveSideType::Enemy:
		if (IsValid(GameInstance))
		{
			FEnemyDataTable* StatTable = GameInstance->GetEnemyInfo(CustomOwner->GetEnemyDataCode());
			if (StatTable != nullptr)
			{
				if (!IsValid(CurStatInfo))
					CurStatInfo = NewObject<UEveStatInfo>();
				CurStatInfo->Init(StatTable);
				SetCalculateCombatGauge(true);
			}
		}
		break;
	case EEveSideType::Player:
	case EEveSideType::Supporter:
		if (IsValid(GameInstance))
		{
			FCharacterStatTable* StatTable = GameInstance->GetStatInfo(TempUnitType);
			if (StatTable != nullptr)
			{
				if (!IsValid(CurStatInfo))
					CurStatInfo = NewObject<UEveStatInfo>();
				CurStatInfo->Init(StatTable);
				SetCalculateCombatGauge(false);
			}
		}
		break;
	}
}

float UStatComponent::GetCurStats(EEveStatType StatType)
{
	// if (const auto Value = CurrentStats.Find(StatType))
	// 	return Value->CurValue;
	switch (StatType)
	{
	case EEveStatType::Health:
		return CurStatInfo->Hp;
	case EEveStatType::Armor:
		return CurStatInfo->Armor;
	case EEveStatType::Damage:
		return CurStatInfo->Damage;
	case EEveStatType::CombatGauge:
		return CurStatInfo->CombatGauge;
	case EEveStatType::HitRecovery:
		return CurStatInfo->HitRecovery;
	}
	return 0.0f; // 스탯이 존재하지 않는 경우 0을 반환하거나 원하는 값을 반환할 수 있습니다.
}

void UStatComponent::RegenStat(EEveStatType statType)
{
	// CurrentStats[statType].CurValue += CurrentStats[statType].RegenValue;
	// OnStatChanged.Broadcast(statType, CurrentStats[statType]);
	// if (CurrentStats[statType].CurValue >= CurrentStats[statType].DefaultValue)
	// {
	// 	GetOwner()->GetWorldTimerManager().ClearTimer(CurrentStats[statType].TimerHandle);
	// }
}

void UStatComponent::ClearAllTimer()
{
	// for (auto Element : CurrentStats)
	// {
	// 	GetOwner()->GetWorldTimerManager().ClearTimer(Element.Value.TimerHandle);
	// }
}

void UStatComponent::ResetStat(EEveStatType StatType)
{
	switch (StatType)
	{
	case EEveStatType::Health:
		CurStatInfo->Hp = CurStatInfo->MaxHp;
		break;
	case EEveStatType::Armor:
		break;
	case EEveStatType::Stamina:
		break;
	case EEveStatType::Mana:
		break;
	case EEveStatType::CombatGauge:
		CurStatInfo->CombatGauge = CurStatInfo->MaxCombatGauge;
		break;
	default: ;
		break;
	}
}

void UStatComponent::ServerResetStat_Implementation(EEveStatType StatType)
{
	MulticastResetStat(StatType);
}


void UStatComponent::MulticastResetStat_Implementation(EEveStatType StatType)
{
	if (!CustomOwner->IsLocallyControlled())
	{
		ResetStat(StatType);
	}
}

void UStatComponent::ModifyCurStat(EEveStatType StatType, float ModifyValue)
{
	switch (StatType)
	{
	case EEveStatType::Health:
		CalculateHP(ModifyValue);
		break;
	case EEveStatType::Armor:
		break;
	case EEveStatType::Stamina:
		break;
	case EEveStatType::Mana:
		break;
	case EEveStatType::CombatGauge:
		CalculateCombatGauge(ModifyValue);
		break;
	default: ;
		break;
	}
}



void UStatComponent::ServerModifyCurStat_Implementation(EEveStatType StatType, float ModifyValue)
{
	MulticastModifyCurStat(StatType, ModifyValue);
}

void UStatComponent::MulticastModifyCurStat_Implementation(EEveStatType StatType, float ModifyValue)
{
	if (!CustomOwner->IsLocallyControlled())
	{
		ModifyCurStat(StatType, ModifyValue);
	}
}

void UStatComponent::CalculateCombatGauge(int ModifyValue)
{
	CurStatInfo->CombatGauge = FMath::Clamp(CurStatInfo->CombatGauge + ModifyValue, 0.0f,
	                                        CurStatInfo->MaxCombatGauge);
	if (CurStatInfo->CombatGauge <= 0)
	{
		CustomOwner->CombatIncapacitatedTrigger();
	}
}

void UStatComponent::CalculateHP(int ModifyValue)
{
	CurStatInfo->Hp = FMath::Clamp(CurStatInfo->Hp + ModifyValue, 0.0f,
												   CurStatInfo->MaxHp);
	if (CurStatInfo->Hp <= 0)
	{
		// ClearAllTimer();
		CustomOwner->DeathTrigger();
	}
}

void UStatComponent::ModifyDamage(UEveDamageInfo* DamageInfo)
{
	CalculateHP(DamageInfo->Damage);
	if (!IsCalculateCombatGauge)
		return;
	if (CustomOwner->GetSideType() == EEveSideType::Enemy)
	{
		CalculateCombatGauge(DamageInfo->CombatGauge);
	}
}
void UStatComponent::ServerModifyDamage_Implementation(UEveDamageInfo* DamageInfo)
{
	MulticastModifyDamage(DamageInfo);
}

void UStatComponent::MulticastModifyDamage_Implementation(UEveDamageInfo* DamageInfo)
{
	if (!CustomOwner->IsLocallyControlled())
	{
		ModifyDamage(DamageInfo);
	}
}

float UStatComponent::GetCurDamage()
{
	return GetCurStats(EEveStatType::Damage);
}

int UStatComponent::GetCurHitRecovery()
{
	return GetCurStats(EEveStatType::HitRecovery);
}

int UStatComponent::GetCurHP()
{
	return GetCurStats(EEveStatType::Health);
}

int UStatComponent::GetCurArmor()
{
	return GetCurStats(EEveStatType::Armor);
}

int UStatComponent::GetCurCombatGauge()
{
	return GetCurStats(EEveStatType::CombatGauge);
}
