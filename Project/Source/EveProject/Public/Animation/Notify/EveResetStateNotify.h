// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EveResetStateNotify.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UEveResetStateNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimNotify", meta = (AllowPrivateAccess = "true"))
	float DelayHideTime;
};
