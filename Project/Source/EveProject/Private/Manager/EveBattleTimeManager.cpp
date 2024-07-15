// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EveBattleTimeManager.h"


// Sets default values
AEveBattleTimeManager::AEveBattleTimeManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEveBattleTimeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEveBattleTimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeTickDelegate.Broadcast(DeltaTime);
}

