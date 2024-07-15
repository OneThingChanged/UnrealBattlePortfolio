// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EveSoundNotify.generated.h"

class UAkAudioEvent;
class USoundCue;
UCLASS()
class EVEPROJECT_API UEveSoundNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
public:
	UPROPERTY(EditAnywhere, Category = "AnimNotify", meta = (DisplayName = "SoundCue"))
	USoundCue* Sound;

	UPROPERTY(EditAnywhere, Category = "AnimNotify", meta = (DisplayName = "SoundEvent"))
	UAkAudioEvent* HitSoundEvent;
	
	UPROPERTY(EditAnywhere, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))
	FName SocketName;
};
