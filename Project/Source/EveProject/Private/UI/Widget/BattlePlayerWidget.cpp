// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/BattlePlayerWidget.h"

#include "Component/CombatComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Player/EvePlayerController.h"
#include "UI/Widget/BattleSkillButtonWidget.h"
#include "Components/SizeBox.h"
#include "CustomClass/InfoClass/EveStatInfo.h"

void UBattlePlayerWidget::Reset()
{
	if (IsValid(V_ComboCanvas))
	{
		V_ComboCanvas->SetVisibility(ESlateVisibility::Hidden);
	}
	bIsActiveComboPanel = false;
}

void UBattlePlayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattlePlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();


	Reset();
	W_NormalAttackButton->OnClickSkillButton.AddDynamic(this, &UBattlePlayerWidget::OnClickedNormalAttack);
	W_Skill1Button->OnClickSkillButton.AddDynamic(this, &UBattlePlayerWidget::OnClickedSkill1);
	W_UltimateButton->OnClickSkillButton.AddDynamic(this, &UBattlePlayerWidget::OnClickedUltimate);
	W_BattleCharButton1->SetIndex(0);
	W_BattleCharButton2->SetIndex(1);
	W_BattleCharButton3->SetIndex(2);

	SupportCharButtons.Add(W_BattleCharButton1);
	SupportCharButtons.Add(W_BattleCharButton2);
	SupportCharButtons.Add(W_BattleCharButton3);
}

void UBattlePlayerWidget::OnClickedNormalAttack()
{
	AEvePlayerController* PlayerController = Cast<AEvePlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		PlayerController->NormalAttackStart();
	}
}

void UBattlePlayerWidget::OnClickedSkill1()
{
	AEvePlayerController* PlayerController = Cast<AEvePlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		PlayerController->Skill1Start();
	}
}

void UBattlePlayerWidget::OnClickedUltimate()
{
	AEvePlayerController* PlayerController = Cast<AEvePlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		PlayerController->UltimateStart();
	}
}

void UBattlePlayerWidget::UpdatePlayerCharacterUI(UEveStatInfo* StatInfo)
{
	if (IsValid(V_HP_ProgressBar))
	{
		static const float OverrideProgressWidth = 250.f;
		static const float OverrideProgressMaxWidth = 280.f;

		float HpRatio = static_cast<float>(StatInfo->Hp) / StatInfo->MaxHp;
		V_HP_ProgressBar->SetPercent(HpRatio);

		if (IsValid(V_Shield_ProgressBar))
		{
			USizeBox* ParentSizeBox = Cast<USizeBox>(V_Shield_ProgressBar->GetParent());
			if (IsValid(ParentSizeBox))
			{
				float HpPlusSheild = StatInfo->Hp + StatInfo->Shield;
				float ShieldRatio = static_cast<float>(HpPlusSheild) / StatInfo->MaxHp;
				if (ShieldRatio <= 1.f)
				{
					V_Shield_ProgressBar->SetPercent(ShieldRatio);
					ParentSizeBox->SetWidthOverride(OverrideProgressWidth);
				}
				else
				{
					const float WidthPerHp = OverrideProgressWidth / StatInfo->MaxHp;
					float DesiredWidth = HpPlusSheild * WidthPerHp;
					DesiredWidth = FMath::Clamp(DesiredWidth, OverrideProgressWidth, OverrideProgressMaxWidth);
					V_Shield_ProgressBar->SetPercent(1.f);
					ParentSizeBox->SetWidthOverride(DesiredWidth);
				}
			}
		}
	}
	if (IsValid(V_HP_Text))
	{
		FText TotalHpTextFormat = FText::FromString(TEXT("{0}/{1}"));
		FText CurrentHpText;
		if (StatInfo->Shield > 0)
		{
			CurrentHpText = FText::Format(FText::FromString(TEXT("{0}({1})")), StatInfo->Hp, StatInfo->Shield);
		}
		else
		{
			CurrentHpText = FText::AsNumber(StatInfo->Hp);
		}
		FText NewText = FText::Format(TotalHpTextFormat, CurrentHpText, FText::AsNumber(StatInfo->MaxHp));
		V_HP_Text->SetText(NewText);
	}
}

void UBattlePlayerWidget::SetPlayerCharacterUI(FCharacterTable* CharInfo)
{
	auto CombatTexture = Cast<UEveGameInstance>(GetGameInstance())->GetImageFromCombatType(CharInfo->CombatType);
	if (IsValid(CombatTexture))
	{
		V_CombatTypeIcon->SetBrushFromTexture(CombatTexture);	
	}
	
}

void UBattlePlayerWidget::SetCombo(int comboCount)
{
	if (!bIsActiveComboPanel && IsValid(V_ComboCanvas))
	{
		V_ComboCanvas->SetVisibility(ESlateVisibility::Visible);
		bIsActiveComboPanel = true;
	}
	if (IsValid(V_ComboText))
	{
		V_ComboText->SetText(FText::AsNumber(comboCount));
	}
}

void UBattlePlayerWidget::UpdateSkill1UI(UEveSkillInfo* SkillInfo)
{
	W_Skill1Button->TickUI(SkillInfo);
}

void UBattlePlayerWidget::UpdateUltimateUI(UEveSkillInfo* SkillInfo)
{
	W_UltimateButton->TickUI(SkillInfo);
}

void UBattlePlayerWidget::UseSkillEnd(ECharState State)
{
	switch (State)
	{
	case ECharState::Skill1:
		W_Skill1Button->TriggerAfterUseSkill();
		break;
	case ECharState::UltimateSkill:
		W_UltimateButton->TriggerAfterUseSkill();
		break;
	}
}
