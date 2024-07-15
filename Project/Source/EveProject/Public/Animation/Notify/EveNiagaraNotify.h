// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_PlayNiagaraEffect.h"
#include "EveNiagaraNotify.generated.h"


class UAkAudioEvent;
class UNiagaraComponent;
class USoundCue;
UCLASS()
class EVEPROJECT_API UEveNiagaraNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UEveNiagaraNotify();
	
	virtual void PostLoad() override;
	
	UPROPERTY(EditAnywhere, Category = "AnimNotify", meta = (DisplayName = "Niagara System"))
	UNiagaraSystem* NiagaraSystem;

	UPROPERTY(EditAnywhere, Category = "AnimNotify", meta = (DisplayName = "SoundCue"))
	USoundCue* SoundCue;

	UPROPERTY(EditAnywhere, Category = "AnimNotify", meta = (DisplayName = "SoundEvent"))
	UAkAudioEvent* HitSoundEvent;
	
	// Location offset from the socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FVector LocationOffset;

	// Rotation offset from socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FRotator RotationOffset;

	// Scale to spawn the Niagara system at
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FVector Scale;

	// SocketName to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	uint32 Attached : 1;

	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "AnimNotify")
	bool bAbsoluteScale;

	// UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	UNiagaraComponent* SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))
	FQuat RotationOffsetQuat;
};
