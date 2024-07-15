// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Animation/Notify/EveAnimNotify.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/EveCharacter.h"
#include "Eve/Define.h"
#include "Game/EveGameInstance.h"
#include "EveCombatCharacter.generated.h"




class UCombatComponent;
class UStatComponent;
class UDamageComponent;
class UEveDamageInfo;
class UEveStatInfo;
UCLASS()
class EVEPROJECT_API AEveCombatCharacter : public AEveCharacter
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamagePostTrigger, UEveStatInfo*, StatInfo);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDrawUITrigger, UEveStatInfo*, StatInfo);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharDeathTrigger, AEveCombatCharacter*, Character);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitPostTrigger, AEveCombatCharacter*, Character);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharGroggyTrigger, AEveCombatCharacter*, Character);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathTrigger);
	
	AEveCombatCharacter();
	virtual void Init() override;
	virtual void CheckSetNewState(ECharState NewState) override;
	void InputDashStart();
	void InputNormalAttackStart();
	void InputUltimateSkillStart();
	void InputNormalChargeAttack(float GetElapsedTime);
	void InputSkill1Start();
	int GetHitRecovery();
	int GetHP();
	int GetCombatGauge();
	void ToggleTarget();
	void SetTarget();
	bool IsAbleToTarget();
	void GetDamagePoint(UEveDamageInfo* DamagePoint) const;
	void ClearDelegate();



	
	bool AbleToGetDamage(EEveSideType EveSide);
	void CombatIncapacitatedTrigger();
	void ReleaseGroggy();
	void SetOwnerController(AEvePlayerController* EvePlayerController) {OwnerController = EvePlayerController; }


	FOnDamagePostTrigger OnDamagePostTrigger;
	FOnDrawUITrigger OnDrawUITrigger;
	FOnHitPostTrigger OnHitPostTrigger;
	FOnCharDeathTrigger OnCharDeathTrigger;
	FOnCharGroggyTrigger OnCharGroggyTrigger;
	FOnDeathTrigger OnDeathTrigger;
protected:

	virtual void Tick(float DeltaSeconds) override;

	virtual bool SetSkillInfo(ECharState NewState, ECharAction NewAction) override;
	virtual void SetNewState(ECharState NewState, ECharAction NewAction) override;
	virtual void SetForceNewState(ECharState NewState, ECharAction NewAction) override;
	virtual void SetAnimation(ECharState NewState, ECharAction NewAction) override;
	virtual void ResetAction() override;
	//체크용
public:
	bool GetIsServer() const {return bIsServer;}
public:
	void TriggerNormalAttack(ECharAction CharAction);
	void TriggerSkill1();
	void TriggerUltimateSkill();
	void NotifySkill(ESkillType SkillType, int32 SkillIndex);
	bool HitEffect(FVector Location, FRotator Rotation);
	void SetEffectSimulationSpeed(float DelayTime, float SimulationSpeed);
	void SetAniSpeed(float DelayTime, float SimulationSpeed);
	bool HitSound();
	UCombatComponent* GetCombatComponent() const {return CombatComponent; }
	UDamageComponent* GetDamageComponent() const {return DamageComponent; }
	UStatComponent* GetStatComponent() const {return StatComponent; }
	void HitTrigger(bool UseHitMotion);
	void DeathTrigger();

	//모션관련
public:
	bool HasHitMotion();
protected:
	// 각 Niagara 이펙트 컴포넌트의 원래 속도를 저장할 배열
	float CharPlayRate = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EveJin, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EveJin, meta = (AllowPrivateAccess = "true"))
	UDamageComponent* DamageComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EveJin, meta = (AllowPrivateAccess = "true"))
	UStatComponent* StatComponent;


public:
	void SetPlayable();
	void SetSupport();
public:
	void SetEnemy();
	FName GetEnemyDataCode() const {return EnemyDataCode; }

private:
	UPROPERTY(EditAnywhere, Category = EnemyProperty, meta = (AllowPrivateAccess = "true"))
	FName EnemyDataCode;

	//AI
public:
	
};
