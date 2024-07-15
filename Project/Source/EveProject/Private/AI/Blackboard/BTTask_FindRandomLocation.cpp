// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTTask_FindRandomLocation.h"

#include "AI/Blackboard/BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "AI/EveAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EveProject/EveProject.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Find Random Location";
	
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEveAIController* const controller = Cast<AEveAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(controller))
		return EBTNodeResult::Failed;

	APawn* const pawn = controller->GetPawn();
	if (!IsValid(pawn))
		return EBTNodeResult::Failed;
	
	auto const origin = pawn->GetActorLocation();
	UNavigationSystemV1* const navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!IsValid(navSystem))
		return EBTNodeResult::Failed;

	Z_SCREEN_LOG(1, FColor::Black, TEXT("Find RandomLocation (%s)"), *pawn->GetName());
	FNavLocation Loc;
	if (navSystem->GetRandomPointInNavigableRadius(origin, SearchRadius, Loc))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}