// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIComponent.generated.h"

class AAIPatrolPath;
class UBehaviorTree;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EVEPROJECT_API UAIComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	AAIPatrolPath* PatrolPath;
public:
	// Sets default values for this component's properties
	UAIComponent();
	UBehaviorTree* GetBehaviorTree() const;
	AAIPatrolPath* GetPatrolPath() const;
	void SetPatrolPath(AAIPatrolPath* Path);
};
