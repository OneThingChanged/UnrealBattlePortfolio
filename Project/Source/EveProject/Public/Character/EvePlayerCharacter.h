// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EveCombatCharacter.h"
#include "EvePlayerCharacter.generated.h"

class USpringArmComponent;
class UEveCameraComponent;
UCLASS()
class EVEPROJECT_API AEvePlayerCharacter : public AEveCombatCharacter
{
	GENERATED_BODY()
public:
	AEvePlayerCharacter();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UEveCameraComponent* FollowCamera;
};
