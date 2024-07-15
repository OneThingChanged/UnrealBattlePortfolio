// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingDamageActor.generated.h"

UCLASS()
class AFloatingDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloatingDamageActor();

	void Init(float InDamage, FColor InColor);

private:
	UPROPERTY()
	class UWidgetComponent* WidgetComponent;

	float Damage = 0.f;
	FColor Color = FColor::White;

};
