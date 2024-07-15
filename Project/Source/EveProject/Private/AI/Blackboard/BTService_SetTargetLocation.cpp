// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTService_SetTargetLocation.h"

#include "AI/EveAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCharacter.h"
#include "Eve/DefineConst.h"
#include "Kismet/GameplayStatics.h"

UBTService_SetTargetLocation::UBTService_SetTargetLocation()
{
}

void UBTService_SetTargetLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UBTService_SetTargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!IsValid(player))
		return;
	auto const PlayerLocation = player->GetActorLocation();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(EveConst::BlackboardKey_TargetLocation, PlayerLocation);
}
