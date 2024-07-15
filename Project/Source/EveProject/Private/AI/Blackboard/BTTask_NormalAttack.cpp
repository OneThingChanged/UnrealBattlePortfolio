// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTTask_NormalAttack.h"

#include "AI/EveAIController.h"
#include "Character/EveCombatCharacter.h"

UBTTask_NormalAttack::UBTTask_NormalAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Normal Attack";
}

EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// auto OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	// if (OutOfRange)
	// {
	// 	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	// 	return EBTNodeResult::Succeeded;
	// }

	auto controller = Cast<AEveAIController>(OwnerComp.GetAIOwner());
	
	auto* npc = Cast<AEveCombatCharacter>(controller->GetPawn());
	if (MontageHasFinished(npc))
	{
		npc->InputNormalAttackStart();
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_NormalAttack::MontageHasFinished(AEveCombatCharacter* NPC)
{
	return NPC->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(NPC->GetCurrentMontage());
}

