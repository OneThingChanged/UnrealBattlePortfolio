// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/EveContinueNotify.h"

#include "Character/EveCombatCharacter.h"
#include "Component/CombatComponent.h"

void UEveContinueNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp != nullptr)
	{
		const auto EveCharacter = Cast<AEveCombatCharacter>(MeshComp->GetOwner());
		if (EveCharacter != nullptr)
		{
			EveCharacter->GetCombatComponent()->ContinueNormalAttack();
		}
	}
}
