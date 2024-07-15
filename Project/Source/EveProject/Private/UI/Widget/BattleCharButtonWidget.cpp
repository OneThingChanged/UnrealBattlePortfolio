// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/BattleCharButtonWidget.h"

#include "Player/EvePlayerController.h"
#include "UI/Widget/BattleSkillButtonWidget.h"


void UBattleCharButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	W_CharSkillButton->OnClickSkillButton.AddDynamic(this, &UBattleCharButtonWidget::OnClickedCharSkillButton);
	W_CharUltimateButton->OnClickSkillButton.AddDynamic(this, &UBattleCharButtonWidget::OnClickedCharUltimateButton);
}

void UBattleCharButtonWidget::SetIndex(int NewIndex)
{
	index = NewIndex;
}

void UBattleCharButtonWidget::OnClickedCharUltimateButton()
{
	AEvePlayerController* PlayerController = Cast<AEvePlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		PlayerController->CharUltimateSkillStart(index);
	}
}

void UBattleCharButtonWidget::OnClickedCharSkillButton()
{
	AEvePlayerController* PlayerController = Cast<AEvePlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		PlayerController->CharActiveSkillStart(index);
	}
}

void UBattleCharButtonWidget::UseSkillEnd(ECharState State)
{
	switch (State)
	{
	case ECharState::Skill1:
		W_CharSkillButton->TriggerAfterUseSkill();
		break;
	case ECharState::UltimateSkill:
		W_CharUltimateButton->TriggerAfterUseSkill();
		break;
	}
}
