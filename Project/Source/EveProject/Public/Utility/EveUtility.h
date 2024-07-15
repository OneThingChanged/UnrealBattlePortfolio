// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EveUtility.generated.h"

UCLASS()
class EVEPROJECT_API AEveUtility : public AActor
{
	GENERATED_BODY()
	
public:
	static void CustomDrawDebugCapsuleBetweenPoints(UWorld* world, const FVector& Start, const FVector& End, float Radius, const FColor& LineColor, EDrawDebugTrace::Type DrawDebugType);
	static void CustomDrawDebugLine(UWorld* world, const FVector& Start, const FVector& End, const FColor& LineColor, EDrawDebugTrace::Type DrawDebugType);
	static void PrintToScreen(UWorld* world, FString YourMessage, FColor Color = FColor::White, float Duration = 3);

};
