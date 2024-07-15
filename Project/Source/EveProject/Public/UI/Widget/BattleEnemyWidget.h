// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleEnemyWidget.generated.h"

class UCanvasPanel;
class UProgressBar;
class AEveBattleGameState;
class AEveCombatCharacter;
class UEveStatInfo;
UCLASS()
class EVEPROJECT_API UBattleEnemyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetHPProgressBar(UEveStatInfo* StatInfo);
	UFUNCTION()
	void SetCombatProgressBar(UEveStatInfo* StatInfo);
	void UpdateUI();
	void ShowUI(bool onOff);
	UFUNCTION()
	void DeathTrigger(AEveCombatCharacter* Character);

private:
	bool bShowUI;
	bool bIsShowing;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float DisplayTime = 1.f;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* V_Canvas;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* V_HP_GaugeBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* V_Element_GaugeBar;
	UFUNCTION()
	void EveTick(float DeltaTime);
};
