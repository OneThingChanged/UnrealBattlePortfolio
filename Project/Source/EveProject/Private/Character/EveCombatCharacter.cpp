// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EveCombatCharacter.h"

#include "AkAudioDevice.h"
#include "AkAudioEvent.h"
#include "MovieSceneDirectorBlueprintUtils.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Animation/EveAnimInstance.h"
#include "Buff/CombatBuff.h"
#include "Camera/EveCameraComponent.h"
#include "Component/BuffComponent.h"
#include "Component/CombatComponent.h"
#include "Component/DamageComponent.h"
#include "Component/EveAKComponent.h"
#include "Component/StatComponent.h"
#include "Component/StateComponent.h"
#include "Component/TargetComponent.h"
#include "Components/CapsuleComponent.h"
#include "CustomClass/TempClass/EveDamageInfo.h"
#include "Eve/Define.h"
#include "Game/EveGameInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AEveCombatCharacter::AEveCombatCharacter()
{
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	PrimaryActorTick.bCanEverTick = true;
}


void AEveCombatCharacter::Init()
{
	Super::Init();
	StateComponent->Init();
	CombatComponent->Init(this);
	DamageComponent->Init(this);
	StatComponent->Init(this);
}

void AEveCombatCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (UseCurveMove)
	{
		// 현재 재생 중인 몽타주 가져오기
		UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

		if (!IsValid(CurrentMontage) || CurSkillInfo == nullptr)
		{
			ResetCurveMove();
			return;
		}

		// 현재 진행된 시간
		float CurrentPosition = AnimInstance->Montage_GetPosition(CurrentMontage);

		// 총 시간
		float TotalDuration = CurrentMontage->GetPlayLength();

		float Speed = CurSkillInfo->MoveCurve->GetFloatValue(CurrentPosition / TotalDuration) * CurSkillInfo->
			MoveMultiplier;

		FVector NewLocation = GetActorLocation() + GetActorForwardVector() * Speed;
		SetActorLocation(NewLocation);
	}
	if (UseHideInTime)
	{
		TimeToHide -= DeltaSeconds;
		if (TimeToHide < 0)
		{
			GetMesh()->SetVisibility(false);
			UseHideInTime= false;
		}
	}
}

void AEveCombatCharacter::CheckSetNewState(ECharState NewState)
{
	switch (NewState)
	{
	case ECharState::None:
		break;
	case ECharState::Idle:
		break;
	case ECharState::Death:
		break;
	case ECharState::Jumping:
		break;
	case ECharState::Dash:
		break;
	case ECharState::Hitting:
		break;
	case ECharState::NormalAttack:
		break;
	default: ;
	}
}

void AEveCombatCharacter::InputDashStart()
{
	if (StateComponent->AbleToInput(ECharState::Dash))
		TriggerDash();
}

void AEveCombatCharacter::InputNormalAttackStart()
{
	if (CombatComponent->AbleToAttack(ECharState::NormalAttack))
		TriggerNormalAttack(ECharAction::NormalAttack1);
}

void AEveCombatCharacter::InputSkill1Start()
{
	if (CombatComponent->AbleToAttack(ECharState::Skill1))
	{
		TriggerSkill1();
	}
}

void AEveCombatCharacter::InputUltimateSkillStart()
{
	if (CombatComponent->AbleToAttack(ECharState::UltimateSkill))
	{
		ServerSetNewState(ECharState::UltimateSkill, ECharAction::UltimateSkill);
		SetNewState(ECharState::UltimateSkill, ECharAction::UltimateSkill);
	}
}

void AEveCombatCharacter::InputNormalChargeAttack(float GetElapsedTime)
{
	GameInstance->GetSkillInfo(UnitType, ESkillType::Dash);
}

int AEveCombatCharacter::GetHitRecovery()
{
	return StatComponent->GetCurHitRecovery();
}

int AEveCombatCharacter::GetHP()
{
	return StatComponent->GetCurHP();
}

void AEveCombatCharacter::ToggleTarget()
{
	TargetComponent->ToggleTarget();
}

void AEveCombatCharacter::SetTarget()
{
	TargetComponent->EnableLockOn();
}

bool AEveCombatCharacter::IsAbleToTarget()
{
	return StateComponent->GetCurrentState() != ECharState::Death;
}

void AEveCombatCharacter::GetDamagePoint(UEveDamageInfo* DamagePoint) const
{
	GetStatComponent()->ServerModifyDamage(DamagePoint);
	GetStatComponent()->ModifyDamage(DamagePoint);
	// GetStatComponent()->ServerModifyCurStat(EEveStatType::Health, DamagePoint->Damage);
	// GetStatComponent()->ModifyCurStat(EEveStatType::Health, DamagePoint->Damage);
	// GetStatComponent()->CalculateHP(DamagePoint->Damage);
	OnDrawUITrigger.Broadcast(GetStatComponent()->GetStatInfo());
}

void AEveCombatCharacter::ClearDelegate()
{
	OnDamagePostTrigger.Clear();
	OnCharDeathTrigger.Clear();
	OnDrawUITrigger.Clear();
	OnDeathTrigger.Clear();
}

bool AEveCombatCharacter::AbleToGetDamage(EEveSideType EveSide)
{
	if (GetSideType() == EveSide ||	GetStateComponent()->GetCurrentState() == ECharState::Death)
	{
		return false;
	}
	switch (EveSide)
	{
	case EEveSideType::Player:
		if (GetSideType() == EEveSideType::Supporter)
			return false;
		break;
	case EEveSideType::Supporter:
		if (GetSideType() == EEveSideType::Player)
			return false;
		break;
	}
	return true;
}

void AEveCombatCharacter::CombatIncapacitatedTrigger()
{
	if (StateComponent->AbleToGroggy())
	{
		return;
	}
	ServerSetForceNewState(ECharState::Groggy, ECharAction::Groggy);
	SetForceNewState(ECharState::Groggy, ECharAction::Groggy);
	UGroggyState* Buff = NewObject<UGroggyState>(this);
	if (not IsValid(Buff))
	{
		return;
	}

	FGroggyTimeInitParam Param;
	Param.Duration = 2;

	Buff->Init(&Param);

	BuffComponent->StartBuff(Buff);
	OnCharGroggyTrigger.Broadcast(this);
}

void AEveCombatCharacter::ReleaseGroggy()
{
	if (StateComponent->GetCurrentState() == ECharState::Groggy)
	{
		StatComponent->ServerResetStat(EEveStatType::CombatGauge);
		StatComponent->ResetStat(EEveStatType::CombatGauge);
		AnimInstance->Montage_JumpToSection(FName("GetUp"));
		OnDrawUITrigger.Broadcast(GetStatComponent()->GetStatInfo());
	}
}

int AEveCombatCharacter::GetCombatGauge()
{
	return StatComponent->GetCurCombatGauge();
}

void AEveCombatCharacter::SetPlayable()
{
	TargetComponent->SetPlayable();
	SetSideType(EEveSideType::Player);
	StatComponent->SetCalculateCombatGauge(false);
}

void AEveCombatCharacter::SetSupport()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetSideType(EEveSideType::Supporter);
	StatComponent->SetCalculateCombatGauge(false);
}


void AEveCombatCharacter::DeathTrigger()
{
	ServerSetForceNewState(ECharState::Death, ECharAction::Death);
	SetForceNewState(ECharState::Death, ECharAction::Death);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnDrawUITrigger.Broadcast(GetStatComponent()->GetStatInfo());
	OnCharDeathTrigger.Broadcast(this);
	OnDeathTrigger.Broadcast();
	ClearDelegate();
}

bool AEveCombatCharacter::HasHitMotion()
{
	return CurCharInfo->HitMontage.Num() > 0;
}

bool AEveCombatCharacter::SetSkillInfo(ECharState NewState, ECharAction NewAction)
{
	if (GameInstance == nullptr)
	{
		return false;
	}
	switch (NewAction)
	{
	case ECharAction::Dash:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::Dash);
		break;
	case ECharAction::BackDash:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::BackDash);
		break;
	case ECharAction::NormalAttack1:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::NormalAttack01);
		break;
	case ECharAction::NormalAttack2:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::NormalAttack02);
		break;
	case ECharAction::NormalAttack3:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::NormalAttack03);
		break;
	case ECharAction::NormalAttack4:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::NormalAttack04);
		break;
	case ECharAction::Skill1:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::Skill1);
		break;
	case ECharAction::UltimateSkill:
		CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::UltimateSkill);
		break;
	default:
		CurSkillInfo = nullptr;
		return true;
	}

	if (CurSkillInfo != nullptr)
		return true;
	const FString ActorName = GetName();
	UE_LOG(LogTemp, Error, TEXT("스킬데이터를 찾을수없습니다. %s, %s"), *ActorName, *UEnum::GetValueAsString(NewAction));
	return false;
}

void AEveCombatCharacter::SetNewState(ECharState NewState, ECharAction NewAction)
{
	if (!SetSkillInfo(NewState, NewAction))
		return;
	ResetCurveMove();
	if (StateComponent->SetState(NewState)
		&& StateComponent->SetAction(NewAction))
	{
		if (CurSkillInfo != nullptr && CurSkillInfo->UseMoveCurve)
			UseCurveMove = true;
		SetAnimation(NewState, NewAction);
	}
}

void AEveCombatCharacter::SetForceNewState(ECharState NewState, ECharAction NewAction)
{
	if (!SetSkillInfo(NewState, NewAction))
		return;

	ResetCurveMove();
	if (StateComponent->SetState(NewState)
		&& StateComponent->SetAction(NewAction))
	{
		if (CurSkillInfo != nullptr && CurSkillInfo->UseMoveCurve)
			UseCurveMove = true;
		SetAnimation(NewState, NewAction);
	}
}

void AEveCombatCharacter::SetAnimation(ECharState NewState, ECharAction NewAction)
{
	switch (NewState)
	{
	case ECharState::None:
		break;
	case ECharState::Idle:
		break;
	case ECharState::Death:
		AnimInstance->Montage_Play(CurCharInfo->DeathMontage);
		break;
	case ECharState::Jumping:
		break;
	case ECharState::Hitting:
		if (CurCharInfo->HitMontage.Num() > 0 && IsValid(CurCharInfo->HitMontage[0]))
		{
			AnimInstance->Montage_Play(CurCharInfo->HitMontage[0]);
			AnimInstance->Montage_JumpToSection(FName("Hit"), CurCharInfo->HitMontage[0]);
		}
		break;
	case ECharState::Groggy:
		AnimInstance->Montage_Play(CurCharInfo->Groggy);
		break;
	case ECharState::Dash:
	case ECharState::NormalAttack:
	case ECharState::Skill1:
	case ECharState::UltimateSkill:
		AnimInstance->Montage_Play(CurSkillInfo->SkillMontage);
		break;
	default: ;
	}
}

void AEveCombatCharacter::ResetAction()
{
	Super::ResetAction();
}

void AEveCombatCharacter::TriggerNormalAttack(ECharAction CharAction)
{
	if (StateComponent->GetCurrentState() == ECharState::NormalAttack)
	{
		ServerSetNewAction(CharAction);
		SetNewAction(CharAction);
	}
	else
	{
		ServerSetNewState(ECharState::NormalAttack, CharAction);
		SetNewState(ECharState::NormalAttack, CharAction);
	}
}

void AEveCombatCharacter::TriggerSkill1()
{
	ServerSetNewState(ECharState::Skill1, ECharAction::Skill1);
	SetNewState(ECharState::Skill1, ECharAction::Skill1);
}

void AEveCombatCharacter::TriggerUltimateSkill()
{
	ServerSetNewState(ECharState::UltimateSkill, ECharAction::UltimateSkill);
	SetNewState(ECharState::UltimateSkill, ECharAction::UltimateSkill);
}

void AEveCombatCharacter::NotifySkill(ESkillType SkillType, int32 SkillIndex)
{
	DamageComponent->NotifySkill(UnitType, SkillType, SkillIndex);
}

bool AEveCombatCharacter::HitEffect(FVector Location, FRotator Rotation)
{
	if (CurCharInfo->HitEffects.Num() <= 0)
		return false;


	UNiagaraSystem* SelectedEffect = CurCharInfo->HitEffects[FMath::RandRange(0, CurCharInfo->HitEffects.Num() - 1)];
	if (!IsValid(SelectedEffect))
		return false;

	// 나이아가라 이펙트 생성
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SelectedEffect, Location, Rotation);
	return true;
}

void AEveCombatCharacter::SetEffectSimulationSpeed(float DelayTime, float SimulationSpeed)
{
	//히트시 이미시브 밝게하여 맞는연출용
	if (IsValid(DynamicMaterialInstance))
		DynamicMaterialInstance->SetScalarParameterValue(FName("EmissiveParam"), 1.0f);

	// n초 동안 모든 Niagara 이펙트 컴포넌트의 속도를 m배로 줄임
	for (int i = 0; i < NiagaraComponents.Num(); ++i)
	{
		if (IsValid(NiagaraComponents[i]))
		{
			// 	// 현재 이펙트 컴포넌트의 속도를 저장
			// 	float OriginalSpeed = NiagaraComponent->GetCustomTimeDilation();

			// 0.5배로 속도를 변경
			NiagaraComponents[i]->SetCustomTimeDilation(SimulationSpeed);
		}
	}

	// n초 대기 후 모든 이펙트 컴포넌트의 속도를 원래대로 복원
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [&]()
	{
		for (UNiagaraComponent* NiagaraComponent : NiagaraComponents)
		{
			if (!IsValid(NiagaraComponent))
				continue;

			// 저장한 원래 속도로 복원
			NiagaraComponent->SetCustomTimeDilation(CharPlayRate);
		}
		//히트시 이미시브 밝게하여 맞는연출용
		if (IsValid(DynamicMaterialInstance))
			DynamicMaterialInstance->SetScalarParameterValue(FName("EmissiveParam"), 0.0f);
	}, DelayTime, false);
}

void AEveCombatCharacter::SetAniSpeed(float DelayTime, float SimulationSpeed)
{
	AnimInstance->SetPlayRate(this, SimulationSpeed, DelayTime);
}

bool AEveCombatCharacter::HitSound()
{
	if (IsValid(CurCharInfo->HitSoundEvent))
	{
		AKComponent->PlaySound(CurCharInfo->HitSoundEvent);
	}
	if (IsValid(CurCharInfo->HitSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, CurCharInfo->HitSound, GetActorLocation());
	}
	return true;
}

void AEveCombatCharacter::HitTrigger(bool UseHitMotion)
{
	// 캐릭터의 위치와 회전을 가져옴
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();

	if (UseHitMotion && StateComponent->AbleToHit())
	{
		ServerSetForceNewState(ECharState::Hitting, ECharAction::Hitting1);
		SetForceNewState(ECharState::Hitting, ECharAction::Hitting1);
	}

	// HitMontage
	HitEffect(Location, Rotation);

	
}
