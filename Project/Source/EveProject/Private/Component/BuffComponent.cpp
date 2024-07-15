// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BuffComponent.h"
#include "Runtime/Engine/Classes/GameFramework/GameStateBase.h"
#include "EveProject/EveProject.h"

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (not (IsValid(GetWorld()) && IsValid(GetWorld()->GetGameState())))
	{
		return;
	}

	float CurrentServerTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();

	for (int32 Index = 0; Index < BuffArray.Num(); ++Index)
	{
		UBuff * Buff = BuffArray[Index];
		if (IsValid(Buff))
		{
			if (CurrentServerTime >= Buff->GetExperationTime())
			{
				BuffArray.RemoveAt(Index);
				--Index;
				Buff->Stop();
			}
		}
	}

	for (int32 Index = 0; Index < BuffArray.Num(); ++Index)
	{
		Z_SCREEN_LOG(-1, FColor::Cyan, TEXT("Buff[%d] %s (%.1f)"), Index, *BuffArray[Index]->GetName(), BuffArray[Index]->GetRemainTime());
	}
}

void UBuffComponent::StartBuff(UBuff* Buff)
{
	if (IsValid(Buff))
	{
		Buff->Start();
		BuffArray.Add(Buff);
	}
}

