// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EveBattleTimeManager.generated.h"




UCLASS()
class EVEPROJECT_API AEveBattleTimeManager : public AActor
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeTickDelegate, float, DeltaTime);
	// Sets default values for this actor's properties
	AEveBattleTimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimeTickDelegate TimeTickDelegate;
};
