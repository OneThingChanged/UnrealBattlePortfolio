// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTTask_FindPlayerLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/EveAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCombatCharacter.h"
#include "EveProject/EveProject.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Find Player Location";
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEveAIController* const controller = Cast<AEveAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(controller))
		return EBTNodeResult::Failed;

	APawn* const pawn = controller->GetPawn();
	if (!IsValid(pawn))
		return EBTNodeResult::Failed;

	AEveCombatCharacter* const CombatCharacter = Cast<AEveCombatCharacter>(pawn);
	if (!IsValid(CombatCharacter))
		return EBTNodeResult::Failed;
	
	auto PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!IsValid(PlayerCharacter))
		return EBTNodeResult::Failed;

	auto const PlayerLocation = PlayerCharacter->GetActorLocation();
		
	Z_SCREEN_LOG(1, FColor::Black, TEXT("Find TargetLocation (%s) (%s) (%s)"), *pawn->GetName(), *PlayerCharacter->GetName(), *PlayerLocation.ToString());
		
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}