// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Eve/Define.h"
#include "BattleCharButtonWidget.generated.h"

class UBattleSkillButtonWidget;

UCLASS()
class EVEPROJECT_API UBattleCharButtonWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	int index;
public:
	virtual void NativeConstruct() override;

	void SetIndex(int NewIndex);
	
	UFUNCTION()
	void OnClickedCharUltimateButton();

	UFUNCTION()
	void OnClickedCharSkillButton();
	
	UFUNCTION()
	void UseSkillEnd(ECharState State);

public:
	UPROPERTY(meta = (BindWidget))
	UBattleSkillButtonWidget* W_CharUltimateButton;

	UPROPERTY(meta = (BindWidget))
	UBattleSkillButtonWidget* W_CharSkillButton;
};
