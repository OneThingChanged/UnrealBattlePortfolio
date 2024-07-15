// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EveCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "EveBattleGameState.generated.h"

class AEveBattleTimeManager;
class AEveBattleCombatManager;
class AEveSoundManager;
class UBattlePlayerWidget;
class UBattleEnemyWidget;
class AEveCombatCharacter;
UCLASS()
class EVEPROJECT_API AEveBattleGameState : public AGameStateBase
{
	GENERATED_BODY()

	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	AEveBattleTimeManager* GetTimeManager() const {return TimeManager;}
	void AddUnit(AEveCharacter* EveCharacter);
	TArray<AEveCharacter*> Units;
public:
	UBattlePlayerWidget* PlayerWidget;
	UBattleEnemyWidget* EnemyWidget;
	AEveCombatCharacter* CurTarget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEveSoundManager> BPSoundManager;
private:
	bool bIsReady = false;
	AEveBattleTimeManager* TimeManager;
	AEveBattleCombatManager* CombatManager;

	AEveSoundManager* SoundManager;
};
