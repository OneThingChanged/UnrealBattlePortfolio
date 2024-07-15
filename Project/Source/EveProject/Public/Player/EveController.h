// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EveController.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEveController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EVEPROJECT_API IEveController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UIChangeControllerHP() = 0;
};
