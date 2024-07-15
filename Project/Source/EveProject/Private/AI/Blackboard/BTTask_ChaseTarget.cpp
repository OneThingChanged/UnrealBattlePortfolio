// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTTask_ChaseTarget.h"

#include "AI/EveEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChaseTarget::UBTTask_ChaseTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Chase Target";
}

EBTNodeResult::Type UBTTask_ChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* aiController = Cast<AEveEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		auto TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(aiController, TargetLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return  EBTNodeResult::Failed;
}
