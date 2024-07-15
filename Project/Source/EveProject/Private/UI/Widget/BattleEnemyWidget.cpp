// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/BattleEnemyWidget.h"

#include "Character/EveCombatCharacter.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "CustomClass/InfoClass/EveStatInfo.h"
#include "Engine/Canvas.h"
#include "Game/EveBattleGameState.h"
#include "Manager/EveBattleTimeManager.h"

void UBattleEnemyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattleEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	V_Canvas->SetRenderOpacity(0);
}

void UBattleEnemyWidget::SetHPProgressBar(UEveStatInfo* StatInfo)
{
	if (IsValid(V_HP_GaugeBar))
	{
		V_HP_GaugeBar->SetPercent(static_cast<float>(StatInfo->Hp) / StatInfo->MaxHp);
	}
}

void UBattleEnemyWidget::SetCombatProgressBar(UEveStatInfo* StatInfo)
{
	if (IsValid(V_Element_GaugeBar))
	{
		V_Element_GaugeBar->SetPercent(static_cast<float>(StatInfo->CombatGauge) / StatInfo->MaxCombatGauge);
	}
}

void UBattleEnemyWidget::ShowUI(bool onOff)
{
	AEveBattleGameState* SDKGameState = GetWorld()->GetGameState<AEveBattleGameState>();
	bShowUI = onOff;
	if (!bIsShowing)
	{
		SDKGameState->GetTimeManager()->TimeTickDelegate.AddDynamic(this, &UBattleEnemyWidget::EveTick);
	}
	bIsShowing = true;
}

void UBattleEnemyWidget::DeathTrigger(AEveCombatCharacter* Character)
{
	AEveBattleGameState* GameState = GetWorld()->GetGameState<AEveBattleGameState>();
	if (IsValid(GameState))
	{
		ShowUI(false);
	}
}

void UBattleEnemyWidget::EveTick(float DeltaTime)
{
	if (bShowUI)
	{
		V_Canvas->SetRenderOpacity(V_Canvas->GetRenderOpacity() + DeltaTime / DisplayTime);
		if (V_Canvas->GetRenderOpacity() > 1)
		{
			V_Canvas->SetRenderOpacity(1);
			AEveBattleGameState* EveGameState = GetWorld()->GetGameState<AEveBattleGameState>();
			EveGameState->GetTimeManager()->TimeTickDelegate.RemoveDynamic(this, &UBattleEnemyWidget::EveTick);
			bIsShowing = false;
		}
	}
	else
	{
		V_Canvas->SetRenderOpacity(V_Canvas->GetRenderOpacity() - DeltaTime / DisplayTime);
		if (V_Canvas->GetRenderOpacity() < 0)
		{
			V_Canvas->SetRenderOpacity(0);
			AEveBattleGameState* EveGameState = GetWorld()->GetGameState<AEveBattleGameState>();
			EveGameState->GetTimeManager()->TimeTickDelegate.RemoveDynamic(this, &UBattleEnemyWidget::EveTick);
			bIsShowing = false;
		}
	}
}


