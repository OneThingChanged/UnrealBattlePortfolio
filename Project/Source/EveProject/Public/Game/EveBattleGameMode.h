// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EveBattleGameMode.generated.h"



UCLASS()
class EVEPROJECT_API AEveBattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	AEveBattleGameMode();
public:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEveCombatCharacter> PlayerCharacter;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEveCombatCharacter>> SupportChar;

	
};
