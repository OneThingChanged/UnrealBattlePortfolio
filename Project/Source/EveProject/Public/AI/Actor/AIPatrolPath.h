// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Eve/Define.h"
#include "GameFramework/Actor.h"
#include "AIPatrolPath.generated.h"

UCLASS()
class EVEPROJECT_API AAIPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPatrolPath();

	FVector GetPatrolPoint(int const Index) const;
	int Num() const;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(MakeEditWidget="true", AllowPrivateAccess="true"))
	EEveAIPatrolPathType PatrolType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(MakeEditWidget="true", AllowPrivateAccess="true"))
	TArray<FVector> PatrolPoints;
};
