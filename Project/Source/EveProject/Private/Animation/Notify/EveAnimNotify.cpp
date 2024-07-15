// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/EveAnimNotify.h"

#include "Character/EveCombatCharacter.h"

void UEveAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                            const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp != nullptr)
	{
		const auto JinCharacter = Cast<AEveCombatCharacter>(MeshComp->GetOwner());
		if (JinCharacter != nullptr && JinCharacter->GetLocalRole() == ROLE_Authority)
		{
			if (JinCharacter->GetIsServer())
			{
				JinCharacter->NotifySkill(SkillType, SkillIndex);
			}
		}
	}
}
