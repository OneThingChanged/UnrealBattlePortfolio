// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/Notify/EveResetStateNotify.h"
#include "Eve/Define.h"
#include "GameFramework/Character.h"
#include "EveCharacter.generated.h"

class UAIComponent;
class AEvePlayerController;
class UBuffComponent;
class UEveAKComponent;
class UEveAnimInstance;
class UStateComponent;
class UTargetComponent;
class UInputComponent;
class UEveGameInstance;
class UNiagaraComponent;
class UBehaviorTree;
class UAIPerceptionStimuliSourceComponent;
struct FCharacterSkillTable;
struct FCharacterTable;

UCLASS()
class EVEPROJECT_API AEveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEveCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Init();
	void HideInTime(float DelayHideTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 플레이어 컨트롤러에 클라이언트와 서버를 구분하는 변수 추가
	UPROPERTY(Replicated)
	bool bIsServer;
	float TimeToHide = 0.f;
	bool bIsActive = false;

public:
	UStateComponent* GetStateComponent() const { return StateComponent; }
	UTargetComponent* GetTargetComponent() const { return TargetComponent; }
	UEveAKComponent* GetAKComponent() const { return AKComponent; }
	UBuffComponent* GetBuffComponent() const { return BuffComponent; }
	UAIComponent* GetAIComponent() const { return AIComponent; }
	

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void CheckSetNewState(ECharState NewState);
	UFUNCTION()
	virtual void ResetAction();
	void AddNiagaraEffect(UNiagaraComponent* NiagaraComponent);

	EEveControllerType GetControllerType() const { return ControllerType; }
	void SetControllerType(EEveControllerType _ControllerType) { ControllerType = _ControllerType; }

protected:
	virtual void SetAnimation(ECharState NewState, ECharAction NewAction);
	virtual bool SetSkillInfo(ECharState NewState, ECharAction NewAction);
	void TriggerDash();

	UFUNCTION()
	void OnNiagaraSystemFinished(UNiagaraComponent* PSystem);

public:
	void ResetCurveMove();
	EEveUnitType GetUnitType() const { return UnitType; }
	EEveSideType GetSideType() const { return SideType; }
	FCharacterTable* GetCharInfo() const { return CurCharInfo; }
	void SetSideType(EEveSideType NewSide) { SideType = NewSide; }

	virtual void SetForceNewState(ECharState NewState, ECharAction NewAction);
	UFUNCTION(Server, Reliable)
	void ServerSetForceNewState(ECharState NewState, ECharAction NewAction);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetForceNewState(ECharState NewState, ECharAction NewAction);

	virtual void SetNewState(ECharState NewState, ECharAction NewAction);
	UFUNCTION(Server, Reliable)
	void ServerSetNewState(ECharState NewState, ECharAction NewAction);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetNewState(ECharState NewState, ECharAction NewAction);


	virtual void SetNewAction(ECharAction NewAction);
	UFUNCTION(Server, Reliable)
	void ServerSetNewAction(ECharAction NewAction);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetNewAction(ECharAction NewAction);

	bool CheckController();


protected:
	bool UseCurveMove;
	bool UseHideInTime;
	AEvePlayerController* OwnerController;
	EEveControllerType ControllerType = EEveControllerType::Enemy;
	UEveGameInstance* GameInstance;
	FCharacterSkillTable* CurSkillInfo;
	FCharacterTable* CurCharInfo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	UEveAnimInstance* AnimInstance;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	TArray<UNiagaraComponent*> NiagaraComponents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* StimuliSource;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	UStateComponent* StateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	UTargetComponent* TargetComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	UEveAKComponent* AKComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	UBuffComponent* BuffComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UAIComponent* AIComponent;

	UPROPERTY(EditDefaultsOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	EEveUnitType UnitType;

	UPROPERTY(EditDefaultsOnly, Category = "EveJin", meta = (AllowPrivateAccess = "true"))
	EEveSideType SideType = EEveSideType::Enemy;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BaseMaterial;
};
