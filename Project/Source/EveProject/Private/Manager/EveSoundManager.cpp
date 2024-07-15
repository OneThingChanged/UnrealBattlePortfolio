// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EveSoundManager.h"

#include "Components/AudioComponent.h"


void AEveSoundManager::Init()
{
	if (IsValid(IntroBGM))
	{
		AudioComponent->SetSound(IntroBGM);
		AudioComponent->Play();
		// float IntroBGMFadeOutTime = 1.0f; // Adjust as needed
		// float IntroBGMFadeOutStartTime = 0.9f * IntroBGM->GetDuration(); // Start fading out at 0.9 of Intro BGM duration
		// float IntroBGMFadeOutEndTime = IntroBGMFadeOutStartTime + IntroBGMFadeOutTime;

		CurSoundState = Intro;
		AudioComponent->OnAudioFinished.AddDynamic(this, &AEveSoundManager::PlayBGM1);
	}
}

// Sets default values
AEveSoundManager::AEveSoundManager()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);
}

void AEveSoundManager::PlayBGM1()
{
	CurSoundState = BGM1;
	if (IsValid(LoopingBGM))
	{
		AudioComponent->SetSound(LoopingBGM);
		AudioComponent->Play();
	}
}

void AEveSoundManager::CheckPlayPercent(const USoundWave* SoundWave, const float Percent)
{
	switch (CurSoundState)
	{
	case Intro:
		if (Percent > PercentIntro)
		{
			AudioComponent->FadeOut(IntroBGMFadeOutTime, 0.0f, EAudioFaderCurve::Linear);
			PlayBGM1();
		}
		break;
	}
}


