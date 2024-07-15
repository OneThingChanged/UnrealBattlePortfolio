// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/FCharacterTable.h"
#include "Eve/Define.h"
#include "BattlePlayerWidget.generated.h"

class UCanvasPanel;
class UImage;
class AEveCombatCharacter;
class AEvePlayerController;
class UBattleSkillButtonWidget;
class UBattleCharButtonWidget;
class UProgressBar;
class UButton;
class UTextBlock;
class UEveSkillInfo;
/**
 * 
 */
UCLASS()
class EVEPROJECT_API UBattlePlayerWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	bool bIsActiveComboPanel = false;
public:
	void Reset();
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickedNormalAttack();
	UFUNCTION()
	void OnClickedSkill1();
	UFUNCTION()
	void OnClickedUltimate();
	UFUNCTION()
	void UpdatePlayerCharacterUI(UEveStatInfo* StatInfo);
	void SetPlayerCharacterUI(FCharacterTable* CharInfo);
	UFUNCTION()
	void SetCombo(int comboCount);
	UFUNCTION()
	void UpdateSkill1UI(UEveSkillInfo* SkillInfo);
	UFUNCTION()
	void UpdateUltimateUI(UEveSkillInfo* SkillInfo);
	UFUNCTION()
	void UseSkillEnd(ECharState State);

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* V_ComboCanvas;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* V_ComboText;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* V_HP_ProgressBar;

	UPROPERTY(meta = (BindWidgetOptional))
	UProgressBar* V_Shield_ProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* V_HP_Text;

	UPROPERTY(meta = (BindWidget))
	UImage* V_CombatTypeIcon;
	
	UPROPERTY(meta = (BindWidget))
	UBattleSkillButtonWidget* W_NormalAttackButton;

	UPROPERTY(meta = (BindWidget))
	UBattleSkillButtonWidget* W_Skill1Button;

	UPROPERTY(meta = (BindWidget))
	UBattleSkillButtonWidget* W_UltimateButton;

	UPROPERTY(meta = (BindWidget))
	UBattleCharButtonWidget* W_BattleCharButton1;

	UPROPERTY(meta = (BindWidget))
	UBattleCharButtonWidget* W_BattleCharButton2;

	UPROPERTY(meta = (BindWidget))
	UBattleCharButtonWidget* W_BattleCharButton3;

	TArray<UBattleCharButtonWidget*> SupportCharButtons;
};
