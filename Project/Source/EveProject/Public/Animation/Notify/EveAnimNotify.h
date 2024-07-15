// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Eve/Define.h"
#include "EveAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UEveAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimNotify", meta = (AllowPrivateAccess = "true"))
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimNotify", meta = (AllowPrivateAccess = "true"))
	int32 SkillIndex;
};
