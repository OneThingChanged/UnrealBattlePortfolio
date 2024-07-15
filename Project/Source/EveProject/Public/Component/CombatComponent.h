// CopyRight Jin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Eve/Define.h"
#include "Game/EveGameInstance.h"
#include "CombatComponent.generated.h"


class UStateComponent;
class AEveCombatCharacter;
class UEveSkillInfo;
// class CurSkillInfo;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVEPROJECT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	void SetSkillInfo(UEveGameInstance* GameInstance, EEveUnitType TempUnitType, ESkillType TempSkillType);
	TMap<ESkillType, UEveSkillInfo*> GetSkillInfos() {return  CurSkillInfos; }
	void SetTarget(AEveCombatCharacter* PlayerPawn);
	void RemoveTarget();

	UStateComponent* StateComponent;
public:
	// Called when the game starts
	void Init(AEveCombatCharacter* InCustomOwner);
	UFUNCTION()
	void EveTick(float DeltaTime);
	AEveCombatCharacter* GetCustomOwner() const {return CustomOwner;}
	
private:
	UPROPERTY(VisibleInstanceOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	AEveCombatCharacter* Target;
	UPROPERTY(VisibleInstanceOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TArray<AEveCombatCharacter*> Seekers;
	AEveCombatCharacter* CustomOwner;
	//일반 콤보공격시 다음 공격콤보 사용여부
	UPROPERTY(VisibleInstanceOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool SaveNextAttack;
	UPROPERTY(VisibleInstanceOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, UEveSkillInfo*> CurSkillInfos;

public:
	bool AbleToAttack(ECharState State);
	void ResetNormalAttack();
	UFUNCTION()
	void EndStateTrigger(ECharState State);
	void ContinueNormalAttack();
};
