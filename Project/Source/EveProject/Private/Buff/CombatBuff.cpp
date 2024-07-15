// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff/CombatBuff.h"

#include "Character/EveCombatCharacter.h"
#include "Player/EvePlayerController.h"
#include "Game/EveBattleGameState.h"
#include "UI/Widget/BattlePlayerWidget.h"
#include "Component/StatComponent.h"
#include "CustomClass/InfoClass/EveStatInfo.h"

UIncreaseDamage::UIncreaseDamage()
{
	Prop = UBuffProp::Buff;
}

void UIncreaseDamage::Init(FBuffInitParam* Param)
{
	Super::Init(Param);

	FIncreassDamageInitParam* CastedParam = static_cast<FIncreassDamageInitParam*>(Param);
	if (CastedParam != nullptr)
	{
		BaseDamageIncrease = CastedParam->BaseDamageIncrease;
	}
}

void UIncreaseDamage::OnBuffStart()
{
	Super::OnBuffStart();

	AActor* Owner = Cast<AActor>(GetOuter());
	if (not IsValid(Owner))
	{
		return;
	}

	UStatComponent* StatComponent = Owner->FindComponentByClass<UStatComponent>();
	if (IsValid(StatComponent))
	{
		UEveStatInfo* StatInfo = StatComponent->GetStatInfo();
		if (IsValid(StatInfo))
		{
			StatInfo->Damage += BaseDamageIncrease;
		}
	}
}

void UIncreaseDamage::OnBuffEnd()
{
	Super::OnBuffEnd();

	AActor* Owner = Cast<AActor>(GetOuter());
	if (not IsValid(Owner))
	{
		return;
	}

	UStatComponent* StatComponent = Owner->FindComponentByClass<UStatComponent>();
	if (IsValid(StatComponent))
	{
		UEveStatInfo* StatInfo = StatComponent->GetStatInfo();
		if (IsValid(StatInfo))
		{
			StatInfo->Damage -= BaseDamageIncrease;
		}
	}
}

UCreateShield::UCreateShield()
{
	Prop = UBuffProp::Buff;
}

void UCreateShield::Init(FBuffInitParam* Param)
{
	Super::Init(Param);

	FCreateShieldInitParam* CastedParam = static_cast<FCreateShieldInitParam*>(Param);
	if (CastedParam != nullptr)
	{
		Shield = CastedParam->Shield;
	}
}

void UCreateShield::OnBuffStart()
{
	Super::OnBuffStart();

	AActor* Owner = Cast<AActor>(GetOuter());
	if (not IsValid(Owner))
	{
		return;
	}

	UStatComponent* StatComponent = Owner->FindComponentByClass<UStatComponent>();
	if (IsValid(StatComponent))
	{
		UEveStatInfo* StatInfo = StatComponent->GetStatInfo();
		if (IsValid(StatInfo))
		{
			StatInfo->Shield += Shield;
			RemainShield = Shield;

			AEveBattleGameState* GameState = GetWorld()->GetGameState<AEveBattleGameState>();
			if (IsValid(GameState) && GameState->PlayerWidget)
			{
				GameState->PlayerWidget->UpdatePlayerCharacterUI(StatInfo);
			}
		}
	}
}

void UCreateShield::OnBuffEnd()
{
	Super::OnBuffEnd();

	AActor* Owner = Cast<AActor>(GetOuter());
	if (not IsValid(Owner))
	{
		return;
	}

	UStatComponent* StatComponent = Owner->FindComponentByClass<UStatComponent>();
	if (IsValid(StatComponent))
	{
		UEveStatInfo* StatInfo = StatComponent->GetStatInfo();
		if (IsValid(StatInfo))
		{
			StatInfo->Shield -= RemainShield;

			AEveBattleGameState* GameState = GetWorld()->GetGameState<AEveBattleGameState>();
			if (IsValid(GameState) && GameState->PlayerWidget)
			{
				GameState->PlayerWidget->UpdatePlayerCharacterUI(StatInfo);
			}
		}
	}
}

UDecreaseCombo::UDecreaseCombo()
{
	Prop = UBuffProp::Debuff;
}

void UDecreaseCombo::Init(FBuffInitParam* Param)
{
	Super::Init(Param);

	FDecreaseComboInitParam* CastedParam = static_cast<FDecreaseComboInitParam*>(Param);
	if (CastedParam != nullptr)
	{
		DecreaseCombo = CastedParam->DecreaseCombo;
	}
}

void UDecreaseCombo::OnBuffStart()
{
	Super::OnBuffStart();

	APawn* OwnerPawn = Cast<APawn>(GetOuter());
	if (not IsValid(OwnerPawn))
	{
		return;
	}

	AEvePlayerController* EvePC = OwnerPawn->GetController<AEvePlayerController>();
	if (not IsValid(EvePC))
	{
		return;
	}

	EvePC->SetAdditionalHitCount(EvePC->GetAdditionalHitCount() - DecreaseCombo);
}

void UDecreaseCombo::OnBuffEnd()
{
	Super::OnBuffEnd();

	APawn* OwnerPawn = Cast<APawn>(GetOuter());
	if (not IsValid(OwnerPawn))
	{
		return;
	}

	AEvePlayerController* EvePC = OwnerPawn->GetController<AEvePlayerController>();
	if (not IsValid(EvePC))
	{
		return;
	}

	EvePC->SetAdditionalHitCount(EvePC->GetAdditionalHitCount() + DecreaseCombo);
}

UGroggyState::UGroggyState()
{
	Prop = UBuffProp::State;
}

void UGroggyState::Init(FBuffInitParam* Param)
{
	Super::Init(Param);
}

void UGroggyState::OnBuffStart()
{
	Super::OnBuffStart();
}

void UGroggyState::OnBuffEnd()
{
	Super::OnBuffEnd();

	AEveCombatCharacter* OwnerPawn = Cast<AEveCombatCharacter>(GetOuter());
	if (not IsValid(OwnerPawn))
	{
		return;
	}

	OwnerPawn->ReleaseGroggy();
}
