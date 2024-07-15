// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsTargetInRange.generated.h"

class AEveAIController;
class AEveCharacter;
UCLASS()
class EVEPROJECT_API UBTService_IsTargetInRange : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_IsTargetInRange();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	float AttackRange = 100.f;

private:
	AEveAIController* AIController;
	AEveCharacter* AI;
};
