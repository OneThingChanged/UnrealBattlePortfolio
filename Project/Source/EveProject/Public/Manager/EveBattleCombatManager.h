// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EveBattleCombatManager.generated.h"

class UEveStatInfo;

UCLASS()
class EVEPROJECT_API AEveBattleCombatManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEveBattleCombatManager();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
