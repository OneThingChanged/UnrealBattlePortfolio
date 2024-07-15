// CopyRight Jin


#include "Component/CombatComponent.h"

#include "Character/EveCombatCharacter.h"
#include "Component/StateComponent.h"
#include "CustomClass/InfoClass/EveSkillInfo.h"
#include "Game/EveBattleGameState.h"
#include "Manager/EveBattleTimeManager.h"
#include "Player/EvePlayerController.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::Init(AEveCombatCharacter* InCustomOwner)
{
	CustomOwner = InCustomOwner;
	StateComponent = CustomOwner->GetStateComponent();
	
	UEveGameInstance* GameInstance = Cast<UEveGameInstance>(CustomOwner->GetGameInstance());
	if (!IsValid(GameInstance))
	{
		return;
	}
	EEveUnitType TempUnitType = CustomOwner->GetUnitType();
	if (TempUnitType == EEveUnitType::None)
	{
		UE_LOG(LogTemp, Log, TEXT("%s은 Unittype이 None입니다."), *GetName())
		return;
	}
	FCharacterTable* CharacterInfo = GameInstance->GetCharacterInfo(TempUnitType);
	for (const auto TempSkillType : CharacterInfo->OwnSkillList)
	{
		SetSkillInfo(GameInstance, TempUnitType, TempSkillType);
	}
	AEveBattleGameState* SDKGameState = GetWorld()->GetGameState<AEveBattleGameState>();
	SDKGameState->GetTimeManager()->TimeTickDelegate.AddDynamic(this, &UCombatComponent::EveTick);

	StateComponent->OnStateEnd.AddDynamic(this, &UCombatComponent::EndStateTrigger);
}

void UCombatComponent::EveTick(float DeltaTime)
{
	for (auto TempSkillInfo : CurSkillInfos)
	{
		TempSkillInfo.Value->EveTick(DeltaTime);
	}
}

void UCombatComponent::SetSkillInfo(UEveGameInstance* GameInstance, EEveUnitType TempUnitType, ESkillType TempSkillType)
{
	FCharacterSkillTable* SkillInfo = GameInstance->GetSkillInfo(TempUnitType, TempSkillType);
	if (SkillInfo != nullptr)
	{
		UEveSkillInfo* CurSkillInfo = NewObject<UEveSkillInfo>();
		CurSkillInfo->UnitType = TempUnitType;
		CurSkillInfo->SkillType = ESkillType::Skill1;
		CurSkillInfo->SetData(SkillInfo);
		CurSkillInfos.Add(TempSkillType, CurSkillInfo);
	}
}

void UCombatComponent::SetTarget(AEveCombatCharacter* TempTarget)
{
	Target = TempTarget;
}

void UCombatComponent::RemoveTarget()
{
	Target = nullptr;
}

void UCombatComponent::ContinueNormalAttack()
{
	if (SaveNextAttack && StateComponent->GetCurrentState() == ECharState::NormalAttack)
	{
		SaveNextAttack = false;
		ECharAction CurAction = StateComponent->GetCurrentAction();
		switch (CurAction) {
		case ECharAction::NormalAttack1:
			CustomOwner->TriggerNormalAttack(ECharAction::NormalAttack2);
			break;
		case ECharAction::NormalAttack2:
			CustomOwner->TriggerNormalAttack(ECharAction::NormalAttack3);
			break;
		case ECharAction::NormalAttack3:
			CustomOwner->TriggerNormalAttack(ECharAction::NormalAttack4);
			break;
		case ECharAction::NormalAttack4:
			break;
		default:;
		}
	}
}

bool UCombatComponent::AbleToAttack(ECharState State)
{
	switch (State)
	{
	case ECharState::NormalAttack:
		{
			if (StateComponent->GetCurrentState() == ECharState::NormalAttack)
			{
				SaveNextAttack = true;
				return false;
			}
			return StateComponent->AbleToInput(State);
		}
		break;
	case ECharState::UltimateSkill:
		{
			//플레이어용
			if (CustomOwner->GetSideType() == EEveSideType::Player)
			{
				return CurSkillInfos[ESkillType::UltimateSkill]->AbleToUseSkill
				&& StateComponent->AbleToInput(State)
				&& Cast<AEvePlayerController>(CustomOwner->GetController())->GetHitCount(CurSkillInfos[ESkillType::UltimateSkill]->Data->Resource);				
			}
		}
		return CurSkillInfos[ESkillType::UltimateSkill]->AbleToUseSkill && StateComponent->AbleToInput(State);
	case ECharState::Skill1:
		{
			if (CustomOwner->GetSideType() == EEveSideType::Player)
			{
				return CurSkillInfos[ESkillType::Skill1]->AbleToUseSkill
				&& StateComponent->AbleToInput(State)
				&& Cast<AEvePlayerController>(CustomOwner->GetController())->GetHitCount(CurSkillInfos[ESkillType::Skill1]->Data->Resource);				
			}
		}
		return CurSkillInfos[ESkillType::Skill1]->AbleToUseSkill && StateComponent->AbleToInput(State);
	default: ;
	}
	return  false;
}

void UCombatComponent::ResetNormalAttack()
{
	SaveNextAttack = false;
}

void UCombatComponent::EndStateTrigger(ECharState State)
{
		switch (State)
	{
	case ECharState::UltimateSkill:
		CurSkillInfos[ESkillType::UltimateSkill]->AbleToUseSkill = false;
		CurSkillInfos[ESkillType::UltimateSkill]->CurCoolTime = CurSkillInfos[ESkillType::UltimateSkill]->MaxCoolTime; 
		break;
	case ECharState::Skill1:
		CurSkillInfos[ESkillType::Skill1]->AbleToUseSkill = false;
		CurSkillInfos[ESkillType::Skill1]->CurCoolTime = CurSkillInfos[ESkillType::Skill1]->MaxCoolTime; 
	default:
		break;
	}
}