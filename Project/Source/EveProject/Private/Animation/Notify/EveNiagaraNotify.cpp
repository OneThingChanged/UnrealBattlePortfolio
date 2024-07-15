// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/EveNiagaraNotify.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Character/EveCombatCharacter.h"
#include "NiagaraComponent.h"
#include "Component/EveAKComponent.h"
#include "EveProject/EveProject.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UEveNiagaraNotify::PostLoad()
{
	Super::PostLoad();

	RotationOffsetQuat = FQuat(RotationOffset);
}

void UEveNiagaraNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                               const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(SoundCue))
	{
		UGameplayStatics::PlaySoundAtLocation(MeshComp, SoundCue, MeshComp->GetSocketLocation(SocketName));
	}

	if (IsValid(HitSoundEvent))
	{
		FOnAkPostEventCallback nullCallBack;
		UAkGameplayStatics::PostEvent(HitSoundEvent, 
								MeshComp->GetOwner(), 
								0,
								nullCallBack);
	}		
	
	UNiagaraComponent* NiagaraComponent = SpawnEffect(MeshComp, Animation);
	if (!IsValid(NiagaraComponent))
		return;
	
	Super::Notify(MeshComp, Animation, EventReference);

	if (!IsValid(MeshComp))
		return;


	
	const auto JinCharacter = Cast<AEveCombatCharacter>(MeshComp->GetOwner());

	if (!IsValid(JinCharacter))
		return;
	
	JinCharacter->AddNiagaraEffect(NiagaraComponent);
}

UEveNiagaraNotify::UEveNiagaraNotify()	: Super()
{
	Attached = true;
	Scale = FVector(1.f);
	bAbsoluteScale = false;

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(189, 255, 195, 255);
#endif // WITH_EDITORONLY_DATA
}

UNiagaraComponent* UEveNiagaraNotify::SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const
{
	UNiagaraComponent* ReturnComp = nullptr;
	
	if (!IsValid(NiagaraSystem))
		return ReturnComp;
		
	if (NiagaraSystem->IsLooping())
		return ReturnComp;

	if (Attached)
	{
		ReturnComp = UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraSystem, MeshComp,
			SocketName,
			LocationOffset,
			RotationOffset, EAttachLocation::KeepRelativeOffset, true);
	}
	else
	{
		const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);
		ReturnComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(),
			NiagaraSystem,
			MeshTransform.TransformPosition(LocationOffset),
			(MeshComp->GetComponentRotation() + RotationOffset),
			Scale,
			true);
	}

	if (ReturnComp != nullptr)
	{
		ReturnComp->SetUsingAbsoluteScale(bAbsoluteScale);
		ReturnComp->SetRelativeScale3D_Direct(Scale);
	}



	return ReturnComp;
}


