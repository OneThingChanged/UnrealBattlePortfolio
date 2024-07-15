// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EveAIController.generated.h"


/**
 * 
 */
UCLASS()
class EVEPROJECT_API AEveAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AEveAIController();
public:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	float SightRadius = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	float LoseSightRadius = 1100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	float PeripheralVisionAngleDegrees = 45.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	float AutoSuccessRangeFromLastSeenLocation = 520.f;
};
