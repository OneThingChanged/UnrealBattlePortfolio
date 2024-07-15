// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/EveResetStateNotify.h"

#include "Character/EveCharacter.h"
#include "Component/StateComponent.h"

void UEveResetStateNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp != nullptr)
	{
		const auto JinCharacter = Cast<AEveCharacter>(MeshComp->GetOwner());
		if (JinCharacter != nullptr)
			// if (JinCharacter != nullptr && JinCharacter->GetLocalRole() == ROLE_Authority)
		{
			if (JinCharacter->GetSideType() == EEveSideType::Supporter)
			{
				JinCharacter->HideInTime(DelayHideTime);
			}
			else
			{
				JinCharacter->ResetAction();
			}
		}
	}
}
