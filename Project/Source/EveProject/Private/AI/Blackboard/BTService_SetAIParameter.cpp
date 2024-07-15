// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTService_SetAIParameter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCombatCharacter.h"
#include "Component/StateComponent.h"
#include "Eve/DefineConst.h"

UBTService_SetAIParameter::UBTService_SetAIParameter()
{
}

void UBTService_SetAIParameter::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UBTService_SetAIParameter::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (auto Controller = OwnerComp.GetAIOwner())
	{
		if (auto* AI = Cast<AEveCombatCharacter>(Controller->GetPawn()))
		{
			auto CurrentState = AI->GetStateComponent()->GetCurrentState();
			EEveAIState AIState = EEveAIState::Idle;
			switch (CurrentState)
			{
			case ECharState::NormalAttack:
				AIState = EEveAIState::NormalAttack;
				break;
			case ECharState::Idle:
				bool CanSeeTarget = OwnerComp.GetBlackboardComponent()->GetValueAsBool(EveConst::BlackboardKey_CanSeeTarget);
				AIState = CanSeeTarget ? EEveAIState::Chase : EEveAIState::Patrol;
				break;
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EveConst::BlackboardKey_AIStateType, static_cast<int>(AIState));
		}
	}

}
