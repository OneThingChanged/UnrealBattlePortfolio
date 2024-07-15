#pragma once

#include "CoreMinimal.h"
#include "AkAudioEvent.h"
#include "Engine/DataTable.h"
#include "Eve/Define.h"
#include "NiagaraSystem.h"
#include "FCharacterTable.generated.h"

USTRUCT(BlueprintType)
struct FCharacterTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	EEveUnitType UnitType = EEveUnitType::None;

	UPROPERTY(EditAnywhere, Category = "Skill")
	EEveCombatType CombatType = EEveCombatType::None;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TArray<ESkillType> OwnSkillList;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TArray<ECharState> CheckAbleToInputState;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TArray<ECharState> CheckAbleToInputNormalAttack;
	
	UPROPERTY(EditAnywhere, Category = "Skill")
	TArray<ECharState> CheckAbleToMove;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TArray<ECharState> CheckAbleToHit;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TArray<UAnimMontage*> DodgeMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TArray<UAnimMontage*> NormalAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TArray<UAnimMontage*> HitMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* Groggy;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TArray<UNiagaraSystem*> HitEffects;
	
	UPROPERTY(EditAnywhere, Category = "Skill")
	USoundCue* HitSound;

	UPROPERTY(EditAnywhere, Category = "Skill")
	UAkAudioEvent* HitSoundEvent;
};