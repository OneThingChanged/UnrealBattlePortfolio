// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BattleHUD.h"

#include "Blueprint/UserWidget.h"
#include "EveProject/EveProject.h"
#include "Game/EveBattleGameState.h"
#include "Player/EvePlayerController.h"
#include "UI/Widget/BattleEnemyWidget.h"
#include "UI/Widget/BattlePlayerWidget.h"

void ABattleHUD::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("BattleHUD"));
	// PlayerHPWidget = CreateWidget(GetWorld(), PlayerHPWidgetClass.Get());
	PlayerWidget = CreateWidget<UBattlePlayerWidget>(GetWorld(), PlayerWidgetClass);	
	if (IsValid(PlayerWidget))
	{
		PlayerWidget->AddToViewport();
	}
	
	EnemyWidget = CreateWidget<UBattleEnemyWidget>(GetWorld(), EnemyWidgetClass);
	if (IsValid(EnemyWidget))
	{
		EnemyWidget->AddToViewport();
	}
	
	AEveBattleGameState* GameState = GetWorld()->GetGameState<AEveBattleGameState>();
	if (IsValid(GameState))
	{
		GameState->PlayerWidget = PlayerWidget;
		GameState->EnemyWidget = EnemyWidget;
	}
}

void ABattleHUD::DrawHUD()
{
	Super::DrawHUD();
	
}
