// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTTask_FindPathPoint.h"

#include "AI/EveAIController.h"
#include "AI/Actor/AIPatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCharacter.h"
#include "Component/AIComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find PatrolPoint";
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Controller = Cast<AEveAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const BlackboardComponent = OwnerComp.GetBlackboardComponent())
		{
			auto const index = BlackboardComponent->GetValueAsInt(GetSelectedBlackboardKey());
			if (auto* AI = Cast<AEveCharacter>(Controller->GetPawn()))
			{
				AAIPatrolPath* path = AI->GetAIComponent()->GetPatrolPath();
				if (path == nullptr || path->Num() <= index)
				{
					return EBTNodeResult::Failed;
				}
				auto Point = path->GetPatrolPoint(index);

				auto GlobalPoint = AI->GetAIComponent()->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				BlackboardComponent->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return  EBTNodeResult::Failed;
}
