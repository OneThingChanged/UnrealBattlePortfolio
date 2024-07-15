// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EveGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API AEveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AEveGameModeBase();

	virtual void BeginPlay() override;

	
};
