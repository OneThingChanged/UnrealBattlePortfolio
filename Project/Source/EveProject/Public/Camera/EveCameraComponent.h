// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "EveCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class EVEPROJECT_API UEveCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StartCameraShake(float Intensity, float Duration);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StopCameraShake();
	
private:
	FRotator OriginalCameraRotation;
	FTimerHandle ShakeTimerHandle;
};
