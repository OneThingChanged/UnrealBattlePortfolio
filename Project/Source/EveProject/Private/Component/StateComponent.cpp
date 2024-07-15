// CopyRight Jin


#include "Component/StateComponent.h"
#include "Character/EveCombatCharacter.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStateComponent::Reset()
{
	// Owner->ResetState();
	UE_LOG(LogTemp, Log, TEXT(""))
	SetState(DefaultState);
	SetAction(DefaultAction);
}

bool UStateComponent::AbleToInput(ECharState NewState)
{
	// 현재 상태가 제외할 상태 목록에 포함되어 있으면 사용 불가
	for (ECharState ExcludedState : CheckAbleToInputState)
	{
		if (CurrentState == ExcludedState)
		{
			return true;
		}
	}
	return false;
}

bool UStateComponent::AbleToNormalAttack(ECharState NewState)
{
	// 현재 상태가 제외할 상태 목록에 포함되어 있으면 사용 불가
	for (ECharState ExcludedState : CheckAbleToNormalAttack)
	{
		if (CurrentState == ExcludedState)
		{
			return true;
		}
	}
	return false;
}

bool UStateComponent::AbleToMove()
{
	// 현재 상태가 제외할 상태 목록에 포함되어 있으면 사용 불가
	for (ECharState ExcludedState : CheckAbleToMove)
	{
		if (CurrentState == ExcludedState)
		{
			return true;
		}
	}
	return false;
}

bool UStateComponent::AbleToHit()
{
	//히트모션이 없는경우
	if (!CustomOwner->HasHitMotion())
		return false;
	
	// 현재 상태가 제외할 상태 목록에 포함되어 있으면 사용 불가
	for (ECharState ExcludedState : CheckAbleToHit)
	{
		if (CurrentState == ExcludedState)
		{
			return true;
		}
	}
	return false;
}

void UStateComponent::Init()
{
	CustomOwner = Cast<AEveCombatCharacter>(GetOwner());
	if (!IsValid(CustomOwner))
		return;
}

bool UStateComponent::AbleToGroggy()
{
	return CurrentState == ECharState::Death || CurrentState == ECharState::Groggy;
}

ECharState UStateComponent::GetCurrentState()
{
	return CurrentState;
}

bool UStateComponent::SetState(ECharState NewState, bool Force)
{
	if (!Force && CurrentState == NewState)
		return false;

	TriggerOnStateEnd();
	CurrentState = NewState;
	TriggerOnStateBegin();
	return true;
}




void UStateComponent::TriggerOnStateBegin()
{
	OnStateBegin.Broadcast(CurrentState);
}

void UStateComponent::TriggerOnStateEnd()
{
	OnStateEnd.Broadcast(CurrentState);
}

ECharAction UStateComponent::GetCurrentAction()
{
	return CurrentAction;
}

bool UStateComponent::SetAction(ECharAction NewAction, bool Force)
{
	if (!Force && CurrentAction == NewAction)
		return false;

	TriggerOnActionEnd();
	CurrentAction = NewAction;
	TriggerOnActionBegin();
	return true;
}

void UStateComponent::TriggerOnActionBegin()
{
	OnActionBegin.Broadcast(CurrentAction);
}

void UStateComponent::TriggerOnActionEnd()
{
	OnActionEnd.Broadcast(CurrentAction);
}
