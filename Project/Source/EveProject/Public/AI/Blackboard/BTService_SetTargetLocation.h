// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UBTService_SetTargetLocation : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SetTargetLocation();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
