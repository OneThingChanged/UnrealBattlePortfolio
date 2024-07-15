// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EveGameModeBase.h"

#include "GameFramework/GameUserSettings.h"

AEveGameModeBase::AEveGameModeBase()
{

}

void AEveGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	UserSettings->bUseVSync = true;
}
