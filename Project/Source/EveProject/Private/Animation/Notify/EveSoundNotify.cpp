// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/EveSoundNotify.h"

#include "AkGameplayStatics.h"
#include "Character/EveCombatCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UEveSoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	if (!IsValid(MeshComp))
		return;
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (IsValid(Sound))
	{
		UGameplayStatics::PlaySoundAtLocation(MeshComp, Sound, MeshComp->GetSocketLocation(SocketName));
	}

	if (IsValid(HitSoundEvent))
	{
		FOnAkPostEventCallback nullCallBack;
		UAkGameplayStatics::PostEvent(HitSoundEvent, 
								MeshComp->GetOwner(), 
								0,
								nullCallBack);
	}
}
