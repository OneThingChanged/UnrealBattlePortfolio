// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff/Buff.h"
#include "GameFramework/GameStateBase.h"

void UBuff::Init(FBuffInitParam* Param)
{
	Duration = Param->Duration;
}

void UBuff::Start()
{
	if (bActivate)
	{
		return;
	}

	if (not IsValid(GetWorld()))
	{
		return;
	}

	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (not IsValid(GameState))
	{
		return;
	}

	ExpirationServerTime = GameState->GetServerWorldTimeSeconds() + Duration;
	bActivate = true;

	OnBuffStart();
}

void UBuff::Stop()
{
	if (not bActivate)
	{
		return;
	}

	OnBuffEnd();
	ConditionalBeginDestroy();
}

float UBuff::GetExperationTime() const
{
	return ExpirationServerTime;
}

float UBuff::GetRemainTime() const
{
	if (not bActivate)
	{
		return 0.f;
	}

	if (not IsValid(GetWorld()))
	{
		return 0.f;
	}

	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (not IsValid(GameState))
	{
		return 0.f;
	}

	return ExpirationServerTime - GameState->GetServerWorldTimeSeconds();
}
