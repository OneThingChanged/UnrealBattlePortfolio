// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTTask_IncrementPathIndex.h"

#include "AI/EveAIController.h"
#include "AI/Actor/AIPatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCharacter.h"
#include "Component/AIComponent.h"
#include "Eve/Define.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Increment Patrol Index";
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto AIController = Cast<AEveAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto const EnemyBase = Cast<AEveCharacter>(AIController->GetPawn()))
		{
			if (auto* BlackboardComponent = OwnerComp.GetBlackboardComponent())
			{
				auto NumOfPoints = EnemyBase->GetAIComponent()->GetPatrolPath()->Num();
				auto MinIndex = 0;
				auto MaxIndex = NumOfPoints - 1;
				auto Index = BlackboardComponent->GetValueAsInt(GetSelectedBlackboardKey());

				if (BiDirectional)
				{
					if (Index >= MaxIndex && Direction == EEveDirectionType::Forward)
					{
						Direction = EEveDirectionType::Reverse;
					}
					else if (Index <= MinIndex && Direction == EEveDirectionType::Reverse)
					{
						Direction = EEveDirectionType::Forward;
					}
				}

				BlackboardComponent->SetValueAsInt(
					GetSelectedBlackboardKey(),
					(Direction == EEveDirectionType::Forward ? ++Index : --Index) % NumOfPoints);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
