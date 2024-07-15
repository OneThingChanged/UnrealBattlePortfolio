// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Eve/Define.h"
#include "DamageComponent.generated.h"

struct FCharacterSkillTable;

namespace EDrawDebugTrace
{
	enum Type : int;
}


class AEveCombatCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EVEPROJECT_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageComponent();
	void AttackHitTrigger(const FCharacterSkillTable* SkillInfo);
	void Init(AEveCombatCharacter* InCustomOwner);
	void NotifySkill(EEveUnitType UnitType, ESkillType SkillType, int32 SkillIndex);
private:
	AEveCombatCharacter* CustomOwner;

	bool DamageCalculate(USkeletalMeshComponent* _Mesh, const FCharacterSkillTable* SkillInfo, int Index, AEveCombatCharacter* AttackerChar, AEveCombatCharacter* HitCharacter);

	void DamageTriggerForAreaType(const FCharacterSkillTable* SkillInfo, int32 _Index, USkeletalMeshComponent* _Mesh, TArray<AActor*> _GetHitActors);
	void DamageTriggerForSectorType(const FCharacterSkillTable* SkillInfo, int32 _Index, USkeletalMeshComponent* _Mesh, TArray<AActor*> _GetHitActors);

private:
	UPROPERTY(EditAnywhere, Category = EveJin, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EDrawDebugTrace::Type> DebugType;

	UPROPERTY(EditAnywhere, Category = EveJin, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake;
	
};
