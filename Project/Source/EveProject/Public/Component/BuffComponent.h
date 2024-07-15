// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff/Buff.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS()
class UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void StartBuff(UBuff* Buff);

private:
	UPROPERTY()
	TArray<UBuff*> BuffArray;

};
