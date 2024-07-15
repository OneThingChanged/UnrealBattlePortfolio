// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "EveCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class UEveCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(exec)
	void Dev_BuffIncreaseDamage(float BaseDamageIncrease, float Duration);
	UFUNCTION(exec)
	void Dev_BuffCreateShield(int32 Shield, float Duration);
	UFUNCTION(exec)
	void Dev_BuffDecreseCombo(int32 DecreaseCombo, float Duration);

};
