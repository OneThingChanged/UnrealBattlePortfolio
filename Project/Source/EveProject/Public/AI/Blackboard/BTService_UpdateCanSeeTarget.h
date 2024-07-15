// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateCanSeeTarget.generated.h"

class AEveCharacter;
class AEveAIController;
/**
 * 
 */
UCLASS()
class EVEPROJECT_API UBTService_UpdateCanSeeTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_UpdateCanSeeTarget();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AEveAIController* AIController;
	AEveCharacter* AI;
};
