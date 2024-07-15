// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetAIParameter.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UBTService_SetAIParameter : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetAIParameter();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
