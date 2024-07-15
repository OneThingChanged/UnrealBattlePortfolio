// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EveAnimInstance.h"

UEveAnimInstance::UEveAnimInstance() : Super()
{
	PlayRate = 1;
}

void UEveAnimInstance::SetPlayRate(AActor* Actor, float Speed, float DelayTime)
{
	UAnimMontage* Montage = GetCurrentActiveMontage();
	if (Montage)
	{
		FAnimMontageInstance* MontageInstance = GetActiveInstanceForMontage(Montage);
		if (MontageInstance)
		{
			// PlayRate = MontageInstance->GetPlayRate();
			MontageInstance->SetPlayRate(Speed);
		}
	}
	else
	{
		// If no Montage reference, do it on all active ones.
		for (int32 InstanceIndex = 0; InstanceIndex < MontageInstances.Num(); InstanceIndex++)
		{
			FAnimMontageInstance* MontageInstance = MontageInstances[InstanceIndex];
			if (MontageInstance && MontageInstance->IsActive())
			{
				// PlayRate = MontageInstance->GetPlayRate();
				MontageInstance->SetPlayRate(Speed);
			}
		}
	}	
	// GetWorldTimerManager().SetTimer(NavmeshDelayTimer, this, &AFunctionalAITestBase::StartSpawning, 0.5f, false);
	// 1초 대기 후 원래 속도로 돌림
	Actor->GetWorldTimerManager().ClearTimer(TimerHandle);
	Actor->GetWorldTimerManager().SetTimer(TimerHandle, this, &UEveAnimInstance::temp
	, DelayTime, false);
}

void UEveAnimInstance::temp(){
	UAnimMontage* Montage = GetCurrentActiveMontage();
	FAnimMontageInstance* MontageInstance = GetActiveInstanceForMontage(Montage);
	if (MontageInstance)
	{
		// PlayRate = MontageInstance->GetPlayRate();
		MontageInstance->SetPlayRate(PlayRate);
	}
	// Montage_SetPlayRate(GetCurrentActiveMontage(), PlayRate);
}