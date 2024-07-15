// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomClass/InfoClass/EveStatInfo.h"

#include "..\..\Public\Data\FEnemyDataTable.h"
#include "Data/FCharacterStatTable.h"

void UEveStatInfo::Init(FEnemyDataTable* Data)
{
	MaxHp = Hp = Data->Hp;
	BaseDamage = Damage = Data->Damage;
	BaseArmor = Armor = Data->Armor;
	BaseHitRecovery = HitRecovery = Data->HitRecovery;
	MaxCombatGauge = CombatGauge = Data->CombatGauge;
	
	CombatRecoveryTime = Data->CombatRecoveryTime;
	CombatTypes.Empty();
	for (auto Element : Data->CombatTypes)
	{
		CombatTypes.Add(Element);
	}
}

void UEveStatInfo::Init(FCharacterStatTable* Data)
{
	for (auto tempData : Data->Stats)
	{
		switch (tempData.StatType)
		{
		case EEveStatType::Health:
			Hp = tempData.CurValue;
			MaxHp = tempData.DefaultValue;
			break;
		case EEveStatType::Damage:
			Damage = tempData.CurValue;
			BaseDamage = tempData.DefaultValue;
			break;
		case EEveStatType::Armor:
			Armor = tempData.CurValue;
			BaseArmor = tempData.DefaultValue;
			break;
		case EEveStatType::HitRecovery:
			HitRecovery = tempData.CurValue;
			BaseHitRecovery = tempData.DefaultValue;
			break;
		}
	}
}
