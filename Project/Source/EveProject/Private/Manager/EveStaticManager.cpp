// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EveStaticManager.h"

#include "CustomClass/TempClass/EveDamageInfo.h"

// #include "CustomClass/TempClass/EveDamageInfo.h"
TQueue<UEveDamageInfo*> AEveStaticManager::DamageInfoQueue;
// AEveStaticManager* AEveStaticManager::GetInstance()
// {
// 	if (!SingletonInstance)
// 	{
// 		SingletonInstance = NewObject<UMySingleton>();
// 		SingletonInstance->AddToRoot(); // Ensure it's not garbage collected
// 	}
//
// 	return SingletonInstance;
// }

UEveDamageInfo* AEveStaticManager::DequeueDamageInfo()
{
	UEveDamageInfo* temp;
	if (DamageInfoQueue.Dequeue(temp))
		return temp;
	return NewObject<UEveDamageInfo>();
}

void AEveStaticManager::EnqueueDamageInfo(UEveDamageInfo* DamageInfo)
{
	DamageInfoQueue.Enqueue(DamageInfo);
	
}

//
// void AEveStaticManager::EnqueueDamageInfo(UEveDamageInfo* DamageInfo)
// {
// 	DamageInfoQueue.Enqueue(DamageInfo);
// }

