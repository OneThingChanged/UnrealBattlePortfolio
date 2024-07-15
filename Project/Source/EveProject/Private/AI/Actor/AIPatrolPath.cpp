// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Actor/AIPatrolPath.h"

// Sets default values
AAIPatrolPath::AAIPatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector AAIPatrolPath::GetPatrolPoint(int const Index) const
{
	return PatrolPoints[Index];
}

int AAIPatrolPath::Num() const
{
	return PatrolPoints.Num();
}
