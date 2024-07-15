// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EveSoundManager.generated.h"
class USoundBase;
class UAudioComponent;

UCLASS()
class EVEPROJECT_API AEveSoundManager : public AActor
{
	GENERATED_BODY()
	enum SoundState
	{
		None,
		Intro,
		BGM1,
		BGM2,
	};
public:
	void Init();
	// Sets default values for this actor's properties
	AEveSoundManager();

	SoundState CurSoundState = None;
	
	UFUNCTION()
	void PlayBGM1();

	UFUNCTION()
	void CheckPlayPercent(const USoundWave* SoundWave, const float Percent);
	
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundWave* IntroBGM;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundWave* LoopingBGM;

	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
	float PercentIntro = 0.9;
	UPROPERTY(EditAnywhere)
	float IntroBGMFadeOutTime = 1.f;
};
