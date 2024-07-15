// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EveCheatManager.h"
#include "Buff/CombatBuff.h"
#include "Component/BuffComponent.h"

void UEveCheatManager::Dev_BuffIncreaseDamage(float BaseDamageIncrease, float Duration)
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (not IsValid(Pawn))
	{
		return;
	}

	UBuffComponent* BuffComponent = Pawn->FindComponentByClass<UBuffComponent>();
	if (not IsValid(BuffComponent))
	{
		return;
	}

	UIncreaseDamage* Buff = NewObject<UIncreaseDamage>(Pawn);
	if (not IsValid(Buff))
	{
		return;
	}

	FIncreassDamageInitParam Param;
	Param.BaseDamageIncrease = BaseDamageIncrease;
	Param.Duration = Duration;

	Buff->Init(&Param);

	BuffComponent->StartBuff(Buff);
}

void UEveCheatManager::Dev_BuffCreateShield(int32 Shield, float Duration)
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (not IsValid(Pawn))
	{
		return;
	}

	UBuffComponent* BuffComponent = Pawn->FindComponentByClass<UBuffComponent>();
	if (not IsValid(BuffComponent))
	{
		return;
	}

	UCreateShield* Buff = NewObject<UCreateShield>(Pawn);
	if (not IsValid(Buff))
	{
		return;
	}

	FCreateShieldInitParam Param;
	Param.Shield = Shield;
	Param.Duration = Duration;

	Buff->Init(&Param);

	BuffComponent->StartBuff(Buff);
}

void UEveCheatManager::Dev_BuffDecreseCombo(int32 DecreaseCombo, float Duration)
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (not IsValid(Pawn))
	{
		return;
	}

	UBuffComponent* BuffComponent = Pawn->FindComponentByClass<UBuffComponent>();
	if (not IsValid(BuffComponent))
	{
		return;
	}

	UDecreaseCombo* Buff = NewObject<UDecreaseCombo>(Pawn);
	if (not IsValid(Buff))
	{
		return;
	}

	FDecreaseComboInitParam Param;
	Param.DecreaseCombo = DecreaseCombo;
	Param.Duration = Duration;

	Buff->Init(&Param);

	BuffComponent->StartBuff(Buff);
}
