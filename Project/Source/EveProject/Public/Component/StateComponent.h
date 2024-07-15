// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Eve/Define.h"
#include "StateComponent.generated.h"

class AEveCombatCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventOnStateBeginDelegate, ECharState, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventOnStateEndDelegate, ECharState, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventOnActionBeginDelegate, ECharAction, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventOnActionEndDelegate, ECharAction, State);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVEPROJECT_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()
	AEveCombatCharacter* CustomOwner;
public:	
	// Sets default values for this component's properties
	UStateComponent();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void Reset();

	bool AbleToInput(ECharState NewState);
	bool AbleToNormalAttack(ECharState NewState);
	bool AbleToMove();
	bool AbleToHit();

	void Init();
	void SetCheckAbleToInputState(TArray<ECharState> State) {CheckAbleToInputState = State; }
	void SetCheckAbleToNormalAttackState(TArray<ECharState> State) {CheckAbleToNormalAttack = State; }
	void SetCheckAbleToMove(TArray<ECharState> State) {CheckAbleToMove = State; }
	void SetCheckAbleToHit(TArray<ECharState> State) {CheckAbleToHit = State; }
	bool AbleToGroggy();

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TArray<ECharState> CheckAbleToInputState;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TArray<ECharState> CheckAbleToNormalAttack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TArray<ECharState> CheckAbleToMove;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TArray<ECharState> CheckAbleToHit;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	ECharState DefaultState = ECharState::Idle;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	ECharState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	ECharAction DefaultAction = ECharAction::IdleWalkRun;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	ECharAction CurrentAction;
	
	//State
public:
	ECharState GetCurrentState();
	bool SetState(ECharState NewState, bool Force = false);
	
	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FEventOnStateBeginDelegate OnStateBegin;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void TriggerOnStateBegin();


	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FEventOnStateEndDelegate OnStateEnd;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void TriggerOnStateEnd();

	//Action
public:
	ECharAction GetCurrentAction();
	bool SetAction(ECharAction NewAction, bool Force = false);
	
	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FEventOnActionBeginDelegate OnActionBegin;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void TriggerOnActionBegin();

	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FEventOnActionEndDelegate OnActionEnd;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void TriggerOnActionEnd();
};
