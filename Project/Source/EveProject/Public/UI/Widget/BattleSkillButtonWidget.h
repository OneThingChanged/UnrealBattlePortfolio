// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleSkillButtonWidget.generated.h"


class UEveSkillInfo;
class UButton;
class UImage;
class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickSkillButton);

UCLASS()
class EVEPROJECT_API UBattleSkillButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ActiveButton(UEveSkillInfo* CurSkillInfo);
	UFUNCTION()
	void TriggerAfterUseSkill();
	void SetSkillImage(UTexture2D* Image);
	bool bIsActiveButton = false;

	UFUNCTION()
	void OnClicked();
	UFUNCTION()
	void TickUI(UEveSkillInfo* SkillInfo);

	UPROPERTY(meta = (BindWidget))
	UButton* V_SkillButton;

	UPROPERTY(meta = (BindWidget))
	UImage* V_SkillIcon;

	UPROPERTY(meta = (BindWidget))
	UImage* V_ActiveImage;

	UPROPERTY(meta = (BindWidget))
	UImage* V_CoolTimeImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* V_CoolTimeText;

	UPROPERTY(meta = (BindWidget))
	FOnClickSkillButton OnClickSkillButton;
};
