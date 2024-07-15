// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Blackboard/BTDecorator_CheckBool.h"

UBTDecorator_CheckBool::UBTDecorator_CheckBool()
{
	NodeName = "BlackboardBase";

}

void UBTDecorator_CheckBool::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	Super::OnNodeActivation(SearchData);
}

void UBTDecorator_CheckBool::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	Super::OnNodeDeactivation(SearchData, NodeResult);
}
