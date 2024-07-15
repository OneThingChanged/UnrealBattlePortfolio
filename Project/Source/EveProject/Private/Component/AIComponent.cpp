// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AIComponent.h"


// Sets default values for this component's properties
UAIComponent::UAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UBehaviorTree* UAIComponent::GetBehaviorTree() const
{
	return Tree;
}

AAIPatrolPath* UAIComponent::GetPatrolPath() const
{
	return PatrolPath;
}

void UAIComponent::SetPatrolPath(AAIPatrolPath* Path)
{
	PatrolPath = Path;
}

