// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTService_IsTargetInRange.h"

#include "AI/EveAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCombatCharacter.h"
#include "Eve/DefineConst.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsTargetInRange::UBTService_IsTargetInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Target In Range");
}

void UBTService_IsTargetInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AIController = Cast<AEveAIController>(OwnerComp.GetAIOwner());
	AI = Cast<AEveCharacter>(AIController->GetPawn());
}

void UBTService_IsTargetInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	bool targetInRange = AI->GetDistanceTo(player) <= AttackRange;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(EveConst::BlackboardKey_TargetInRange, targetInRange);
}
