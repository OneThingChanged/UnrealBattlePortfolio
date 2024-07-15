// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EveBattleGameState.h"
#include "Character/EveCombatCharacter.h"
#include "Manager/EveBattleTimeManager.h"
#include "Manager/EveSoundManager.h"
#include "UI/Widget/BattlePlayerWidget.h"

void AEveBattleGameState::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("게임 스테이트가 준비되었습니다."));
	TSubclassOf<AEveBattleTimeManager> TimeManagerClass = AEveBattleTimeManager::StaticClass();
	FVector SpawnLocation = FVector(0, 0, 0); // 원하는 스폰 위치로 수정
	FRotator SpawnRotation = FRotator::ZeroRotator; // 원하는 스폰 회전으로 수정
	TimeManager = GetWorld()->SpawnActor<AEveBattleTimeManager>(TimeManagerClass, SpawnLocation, SpawnRotation);
	SoundManager = GetWorld()->SpawnActor<AEveSoundManager>(BPSoundManager, SpawnLocation, SpawnRotation);
	SoundManager->Init();
	bIsReady = true;
	for (auto Unit : Units)
	{
		Unit->Init();
	}
}

void AEveBattleGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEveBattleGameState::AddUnit(AEveCharacter* EveCharacter)
{
	Units.Add(EveCharacter);
	// if (bIsReady)
	// {
	// 	EveCharacter->Init();
	// }
	// else
	// {
	// 	Units.Add(EveCharacter);
	// }
}
