// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EveController.h"
#include "GameFramework/PlayerController.h"
#include "UI/Widget/BattleCharButtonWidget.h"
#include "EvePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class AEveCombatCharacter;
struct FInputActionValue;
struct FInputActionInstance;

UCLASS()
class EVEPROJECT_API AEvePlayerController : public APlayerController
{
	GENERATED_BODY()
	int ComboCount = 0;
	int32 AdditionalHitCount = 0;
	bool OnTriggerAction;
public:
	AEvePlayerController();
	UFUNCTION()
	void HitCount(AEveCombatCharacter* HitCharacter);
	bool GetHitCount(int RequestComboCount);
	void SetAdditionalHitCount(int32 InAdditionalHitCount);
	int32 GetAdditionalHitCount() const;

	void SetUI();
	virtual void PlayerTick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void NormalAttackStart();
	void Skill1Start();
	void UltimateStart();
	void HidePointer();
	void ShowPointer();

	void SetCameraLocation();
	
	UFUNCTION(Exec, Category="Commands")
	void ShowDebugScreen();
	bool GetShowDebug() const {return ShowDebug;}
	void CharUltimateSkillStart(int Index);
	void CharActiveSkillStart(int Index);

public:
	AEveCombatCharacter* CurCharacter;
	TArray<AEveCombatCharacter*> SupportCharacters;
	
private:
	void SetSpringArmLength(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);

	void StartSprint(const FInputActionValue& Value);
	void OnGoingSprint(const FInputActionInstance& Value);
	void EndSprint(const FInputActionValue& Value);

	void StartTriggerButton(const FInputActionValue& Value);
	void EndTriggerButton(const FInputActionValue& Value);
	
	//이동
	void Move(const FInputActionValue& Value);

	//시야 회전
	void Look(const FInputActionValue& Value);

	//회피
	void Dodge(const FInputActionValue& Value);
	
	//타겟
	void ToggleTarget(const FInputActionValue& Value);

	//일반 공격
	void NormalAttackTrigger(const FInputActionInstance& Value);
	void NormalAttackOnGoing(const FInputActionInstance& Value);
	void NormalAttackEnd(const FInputActionInstance& Value);


	void Skill1End(const FInputActionValue& Value);
	void Skill2Start(const FInputActionValue& Value);
	void Skill2End(const FInputActionValue& Value);
	void Skill3Start(const FInputActionValue& Value);
	void Skill3End(const FInputActionValue& Value);

	void UltimateEnd(const FInputActionValue& Value);

	//서포트 스킬
	void Char1Skill(const FInputActionValue& Value);
	void Char2Skill(const FInputActionValue& Value);
	void Char3Skill(const FInputActionValue& Value);

	void SupportCharActiveSkill(int index);
	void Char2ActiveSkill();
	void Char3ActiveSkill();

	void SupportCharUltimateSkill(int index);
public:
	void UIPlayerNormalAttack();
public:
	UPROPERTY(EditAnywhere, Category="Camera")
	float MaxSpringArmLength = 1000;
	UPROPERTY(EditAnywhere, Category="Camera")
	float minSpringArmLength = 400;
	UPROPERTY(EditAnywhere, Category="Camera")
	float DifferArmLength = 10;
	UPROPERTY(EditAnywhere, Category="Camera")
	UCurveFloat* CameraOffsetCurve;
	
	UPROPERTY(EditAnywhere, Category="Init")
	TSubclassOf<class ABattleHUD> BattleHUD;
	
	UPROPERTY(EditAnywhere, Category="Input")
	bool ShowDebug = true;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> DodgeAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ToggleTargetAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShowPointerAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ToggleWalkAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> UltimateSkillAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> NormalAttackAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> Skill1Action;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> Skill2Action;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> Skill3Action;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> UseChar1Skill;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> UseChar2Skill;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> UseChar3Skill;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> TriggerAction;
};
