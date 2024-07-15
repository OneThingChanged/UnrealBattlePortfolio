// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatComponent.h"
#include "Components/ActorComponent.h"
#include "Struct/EveStatData.h"
#include "StatComponent.generated.h"
class UEveDamageInfo;
class UEveStatInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedSignature, EEveStatType, StatType, FEveStatData,
                                             StatInfo);

class AEveCombatCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVEPROJECT_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();
private:
	AEveCombatCharacter* CustomOwner;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	// TMap<EEveStatType, FEveStatData> CurrentStats;
	
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	UEveStatInfo* CurStatInfo;
	bool IsCalculateCombatGauge = false;

public:
	void SetCalculateCombatGauge(bool onOff);
	
	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnAttributeChangedSignature OnStatChanged;
	
	void Init(AEveCombatCharacter* EveCombatCharacter);
	
	float GetCurStats(EEveStatType StatType);
	UEveStatInfo* GetStatInfo() const {return CurStatInfo; }
	void RegenStat(EEveStatType statType);
	void ClearAllTimer();

	void ResetStat(EEveStatType StatType);
	UFUNCTION(Server, Reliable)
	void ServerResetStat(EEveStatType StatType);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastResetStat(EEveStatType StatType);

	void ModifyCurStat(EEveStatType StatType, float ModifyValue);
	UFUNCTION(Server, Reliable)
	void ServerModifyCurStat(EEveStatType StatType, float ModifyValue);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastModifyCurStat(EEveStatType StatType, float ModifyValue);

	void CalculateCombatGauge(int ModifyValue);
	void CalculateHP(int ModifyValue);
	void ModifyDamage(UEveDamageInfo* DamageInfo);
	UFUNCTION(Server, Reliable)
	void ServerModifyDamage(UEveDamageInfo* DamageInfo);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastModifyDamage(UEveDamageInfo* DamageInfo);
	
	float GetCurDamage();
	int GetCurHitRecovery();
	int GetCurHP();
	int GetCurArmor();
	int GetCurCombatGauge();
};
