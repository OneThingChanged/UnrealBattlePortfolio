// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Eve/Define.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TargetComponent.generated.h"

class AEveCharacter; 
class AEveCombatCharacter; 
class USpringArmComponent; 
class UEveCameraComponent; 

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EVEPROJECT_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()
	UTargetComponent();
private:
	FTimerHandle InputDelayTimer;
	AEveCombatCharacter* CustomOwner;
	AController* OwnerController;
	AEveCombatCharacter* Target;
	
	USpringArmComponent* SpringArm;
	UEveCameraComponent* Camera;
private:
	UPROPERTY(VisibleAnywhere, Category = Target)
	bool IgnoreUpdate;
	UPROPERTY(VisibleAnywhere, Category = Target)
	bool HasTarget;
	UPROPERTY(VisibleAnywhere, Category = Target)
	EEveCameraRotationMode CurRotationMode = EEveCameraRotationMode::DirectToMovement;

	UPROPERTY(EditAnywhere, Category = Target, meta = (AllowPrivateAccess = "true"))
	float Radius = 2000;
	UPROPERTY(EditAnywhere, Category = Target, meta = (AllowPrivateAccess = "true"))
	float Degree = 90;
	UPROPERTY(EditAnywhere, Category = Target, meta = (AllowPrivateAccess = "true"))
	EEveCameraRotationMode DefaultRotationMode = EEveCameraRotationMode::OrientToCamera;
	
	UPROPERTY(EditAnywhere, Category = Target, meta = (AllowPrivateAccess = "true"))
	FVector ControlCameraView;
	
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float TargetRotationInterpSpeed = 2;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraPitchWhenTarget = -30;
	
	UPROPERTY(EditAnywhere, Category = Target, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EDrawDebugTrace::Type> DebugType;
private:
	void SetHasTarget(bool bCond);
	void SetRotationMode(EEveCameraRotationMode _RotationMode);

	bool FindTarget();

	AEveCombatCharacter* FindTargetInSector() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:
	
	void Init();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
						   FActorComponentTickFunction* ThisTickFunction) override;
	void UpdateTargetControlRotation();
	void EnableLockOn();
	void DisableLockOn();
	void SetTarget(AEveCombatCharacter* NewTarget);
	void InactiveTargetUI();
	void ActiveTargetUI();
	void SetPlayable();
	UFUNCTION()
	void NoneTarget();

	void SetSpringArmLength(float Length);
	float GetSpringArmLength() {return SpringArm->TargetArmLength;}
	void SetCameraLocation(FVector Location);
	//클라이언트용 (플레이어만 사용함)
	void ToggleTarget();
	bool GetHasTarget() const {return HasTarget;}
	AEveCombatCharacter* GetTarget() const {return Target;}
};
