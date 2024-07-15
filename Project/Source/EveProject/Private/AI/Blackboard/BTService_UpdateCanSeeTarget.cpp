// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTService_UpdateCanSeeTarget.h"

#include "AI/EveAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCharacter.h"
#include "Eve/DefineConst.h"

UBTService_UpdateCanSeeTarget::UBTService_UpdateCanSeeTarget()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Update Can See Target");
}

void UBTService_UpdateCanSeeTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AIController = Cast<AEveAIController>(OwnerComp.GetAIOwner());
	AI = Cast<AEveCharacter>(AIController->GetPawn());
}

void UBTService_UpdateCanSeeTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	bool CanSeeTarget = OwnerComp.GetBlackboardComponent()->GetValueAsBool(EveConst::BlackboardKey_CanSeeTarget);
	if (!IsValid(AIController) || !IsValid(AI) || CanSeeTarget)
	{
		return;
	}

	// //죽은 상태 
	// if (NPC->GetStateComponent()->GetCurrentState() == JinGameplayTags::Character_State_Death)
	// {
	// 	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<int>(EJinAIState::Death));
	// 	return;
	// }
	
	if (CanSeeTarget)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<int>(EEveAIState::Chase));
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<int>(EEveAIState::Patrol));
	}
}
