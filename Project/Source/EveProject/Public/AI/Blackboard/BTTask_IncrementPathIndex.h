// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Eve/Define.h"
#include "BTTask_IncrementPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UBTTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category="Blackboard", meta=(AllowPrivateAccess = "true"))
	bool BiDirectional = false;

	EEveDirectionType Direction = EEveDirectionType::Forward;
};
