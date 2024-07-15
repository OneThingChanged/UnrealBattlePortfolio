// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EveStaticManager.generated.h"

class UEveDamageInfo;

UCLASS()
class EVEPROJECT_API AEveStaticManager : public AActor
{
	GENERATED_BODY()
// public:
	// static AEveStaticManager* GetInstance();
// private:
	
public:
	static TQueue<UEveDamageInfo*> DamageInfoQueue;
	static UEveDamageInfo* DequeueDamageInfo();
	static void EnqueueDamageInfo(UEveDamageInfo* DamageInfo);
};
