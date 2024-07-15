// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EveBattleCombatManager.h"


// Sets default values
AEveBattleCombatManager::AEveBattleCombatManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEveBattleCombatManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEveBattleCombatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

