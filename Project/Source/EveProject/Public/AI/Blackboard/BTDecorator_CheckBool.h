// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_TagCooldown.h"
#include "BTDecorator_CheckBool.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UBTDecorator_CheckBool : public UBTDecorator
{
	GENERATED_BODY()
	UBTDecorator_CheckBool();
	
protected:
	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector BlackboardKey;

	void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override; 
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;
};
