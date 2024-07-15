// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BattleHUD.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API ABattleHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> EnemyWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PartyWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ComboWidgetClass;

	UPROPERTY()
	class UBattlePlayerWidget* PlayerWidget;

	UPROPERTY()
	class UBattleEnemyWidget* EnemyWidget;

	UPROPERTY()
	class UUserWidget* PartyWidget;

	UPROPERTY()
	class UUserWidget* ComboWidget;

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
};
