// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/BattleSkillButtonWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CustomClass/InfoClass/EveSkillInfo.h"

void UBattleSkillButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattleSkillButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(V_SkillButton))
	{
		V_SkillButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClicked);
		ActiveButton(nullptr);
	}
}

void UBattleSkillButtonWidget::ActiveButton(UEveSkillInfo* CurSkillInfo)
{
	bIsActiveButton = true;
	V_CoolTimeImage->SetVisibility(ESlateVisibility::Hidden);
	V_CoolTimeText->SetVisibility(ESlateVisibility::Hidden);
	
	V_ActiveImage->SetVisibility(ESlateVisibility::Visible);
}

void UBattleSkillButtonWidget::TriggerAfterUseSkill()
{
	bIsActiveButton = false;
	V_CoolTimeImage->SetVisibility(ESlateVisibility::Visible);
	V_CoolTimeText->SetVisibility(ESlateVisibility::Visible);

	V_ActiveImage->SetVisibility(ESlateVisibility::Hidden);
}

void UBattleSkillButtonWidget::SetSkillImage(UTexture2D* Image)
{
	V_SkillIcon->SetBrushFromTexture(Image);
}

void UBattleSkillButtonWidget::OnClicked()
{
	OnClickSkillButton.Broadcast();
}



void UBattleSkillButtonWidget::TickUI(UEveSkillInfo* SkillInfo)
{
	if (bIsActiveButton)
		return;
	
	float curCoolTime = SkillInfo->CurCoolTime;
	float maxCoolTime = SkillInfo->MaxCoolTime;
	FNumberFormattingOptions NumberFormat;
	NumberFormat.MaximumFractionalDigits = 1;
	FText RemainingTimeText = FText::AsNumber(curCoolTime, &NumberFormat);
	V_CoolTimeText->SetText(RemainingTimeText);
}
