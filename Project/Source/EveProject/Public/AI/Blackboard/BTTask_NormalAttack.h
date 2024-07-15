// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_NormalAttack.generated.h"

class AEveCombatCharacter;
/**
 * 
 */
UCLASS()
class EVEPROJECT_API UBTTask_NormalAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_NormalAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	bool MontageHasFinished(AEveCombatCharacter* NPC);
	
};
