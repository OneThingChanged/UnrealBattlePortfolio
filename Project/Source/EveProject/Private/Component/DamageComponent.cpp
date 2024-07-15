// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DamageComponent.h"
#include "UI/FloatingDamageActor.h"
#include "Character/EveCombatCharacter.h"
#include "Component/StatComponent.h"
#include "Component/StateComponent.h"
#include "Component/TargetComponent.h"
#include "CustomClass/TempClass/EveDamageInfo.h"
#include "EveProject/EveProject.h"
#include "Game/EveGameInstance.h"
#include "Manager/EveStaticManager.h"
#include "Utility/EveUtility.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDamageComponent::AttackHitTrigger(const FCharacterSkillTable* SkillInfo)
{
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShake);
	//적을 히트할경우 애니무브를 중지합니다.
	CustomOwner->ResetCurveMove();

	float delayTime = SkillInfo->HitRecoveryTime;
	float simulationSpeed = SkillInfo->HitDelaySpeed;

	//공격자 역경직
	CustomOwner->SetEffectSimulationSpeed(delayTime / 1.5f, simulationSpeed);
	CustomOwner->SetAniSpeed(delayTime / 1.5f, simulationSpeed);
}

void UDamageComponent::DamageTriggerForAreaType(const FCharacterSkillTable* SkillInfo, int32 _Index,
                                                USkeletalMeshComponent* _Mesh, TArray<AActor*> _GetHitActors)
{
	TArray<FOverlapResult> OverlappingActors;
	FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	// 무기의 소유자를 Ignore Actors 배열에 추가합니다.
	TraceParams.AddIgnoredActors(_GetHitActors);

	// Sphere 중심에서의 위치
	FVector SphereCenter = CustomOwner->GetActorLocation();

	// Sphere Trace 수행
	bool bHit = GetWorld()->OverlapMultiByObjectType(
		OverlappingActors,
		SphereCenter,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(SkillInfo->Radius),
		TraceParams
	);

	if (!bHit)
	{
		AEveUtility::CustomDrawDebugCapsuleBetweenPoints(GetWorld(), SphereCenter, SphereCenter, SkillInfo->Radius,
		                                                 FColor::Red, DebugType);
		return;
	}

	AttackHitTrigger(SkillInfo);
	bool UseAntiHitMotion = false;
	EEveSideType AttackerSide = CustomOwner->GetSideType();
	for (const FOverlapResult& HitResult : OverlappingActors)
	{
		AActor* HitActor = HitResult.GetActor();
		const auto HitCharacter = Cast<AEveCombatCharacter>(HitActor);
		if (!IsValid(HitActor)
			|| !IsValid(HitCharacter)
			|| !HitCharacter->AbleToGetDamage(AttackerSide))
		{
			continue;
		}

		UseAntiHitMotion |= DamageCalculate(_Mesh, SkillInfo, _Index, CustomOwner, HitCharacter);
	}
	AEveUtility::CustomDrawDebugCapsuleBetweenPoints(GetWorld(), SphereCenter, SphereCenter, SkillInfo->Radius,
	                                                 FColor::Green, DebugType);

	if (UseAntiHitMotion)
		AttackHitTrigger(SkillInfo);
}

void UDamageComponent::DamageTriggerForSectorType(const FCharacterSkillTable* SkillInfo, int32 _Index,
                                                  USkeletalMeshComponent* _Mesh, TArray<AActor*> _GetHitActors)
{
	TArray<FOverlapResult> OverlappingActors;

	FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	// 무기의 소유자를 Ignore Actors 배열에 추가합니다.
	TraceParams.AddIgnoredActors(_GetHitActors);

	// Sphere 중심에서의 위치
	FVector SphereCenter = CustomOwner->GetActorLocation();

	bool bHit = GetWorld()->OverlapMultiByObjectType(
		OverlappingActors,
		SphereCenter,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(SkillInfo->Radius),
		TraceParams
	);

	if (!bHit)
	{
		AEveUtility::CustomDrawDebugCapsuleBetweenPoints(GetWorld(), SphereCenter, SphereCenter, SkillInfo->Radius,
		                                                 FColor::Red, DebugType);
		return;
	}

	// Sphere 중심에서의 방향 벡터
	FVector SphereForwardVector = CustomOwner->GetActorForwardVector();

	// 내 앞의 좌우 30도 이내에 있는 적을 찾는 각도 (cosine 값 사용)
	float CosineThreshold = FMath::Cos(FMath::DegreesToRadians(SkillInfo->Degree));
	EEveSideType AttackerSide = CustomOwner->GetSideType();
	bool UseAntiHitMotion = false;
	for (const FOverlapResult& HitResult : OverlappingActors)
	{
		AActor* HitActor = HitResult.GetActor();
		AEveCombatCharacter* HitCharacter = Cast<AEveCombatCharacter>(HitActor);
		if (!IsValid(HitActor)
			|| !IsValid(HitCharacter)
			|| !HitCharacter->AbleToGetDamage(AttackerSide))
		{
			continue;
		}

		// 적의 위치
		FVector EnemyLocation = HitActor->GetActorLocation();

		// Sphere 중심에서 적으로의 방향 벡터
		FVector ToEnemyVector = (EnemyLocation - SphereCenter).GetSafeNormal();

		// 내가 보는 방향 벡터와 적 방향 벡터의 내적을 계산
		float DotProduct = FVector::DotProduct(SphereForwardVector, ToEnemyVector);

		// 내적 결과가 CosineThreshold보다 크면 30도 이내에 있다고 간주
		if (DotProduct >= CosineThreshold)
		{
			// 공격 트리거를 발생시키거나 원하는 작업 수행
			// Actor를 공격하도록 작업 수행

			AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, EnemyLocation, FColor::Green, DebugType);
			UseAntiHitMotion |= DamageCalculate(_Mesh, SkillInfo, _Index, CustomOwner, HitCharacter);
		}
		else
		{
			AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, EnemyLocation, FColor::Red, DebugType);
		}
	}

	if (UseAntiHitMotion)
		AttackHitTrigger(SkillInfo);
	
	if (DebugType == EDrawDebugTrace::None)
	{
		return;
	}

	// 캐릭터의 위치
	FVector CharacterLocation = CustomOwner->GetActorLocation();

	// 캐릭터의 시야 방향 벡터
	FVector ViewDirection = CustomOwner->GetActorForwardVector();

	// 시야 방향의 회전을 얻음
	FRotator ViewRotation = CustomOwner->GetActorRotation();

	// 좌우 n도 회전값 계산
	float Degree = SkillInfo->Degree;
	FRotator LeftRotation = ViewRotation + FRotator(0, -Degree, 0);
	FRotator RightRotation = ViewRotation + FRotator(0, Degree, 0);

	// 좌우 n도 방향 벡터 계산
	FVector LeftDirection = LeftRotation.Vector();
	FVector RightDirection = RightRotation.Vector();

	// 좌측과 우측 방향으로 길이 radius 만큼 이동한 좌표 계산
	FVector LeftPoint = CharacterLocation + LeftDirection * SkillInfo->Radius;
	FVector RightPoint = CharacterLocation + RightDirection * SkillInfo->Radius;

	AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, LeftPoint, FColor::Blue, DebugType);
	AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, RightPoint, FColor::Blue, DebugType);
	AEveUtility::CustomDrawDebugCapsuleBetweenPoints(GetWorld(), SphereCenter, SphereCenter, SkillInfo->Radius,
	                                                 FColor::Green, DebugType);
}

void UDamageComponent::Init(AEveCombatCharacter* InCustomOwner)
{
	CustomOwner = InCustomOwner;
}

void UDamageComponent::NotifySkill(EEveUnitType UnitType, ESkillType SkillType, int32 SkillIndex)
{
	USkeletalMeshComponent* mesh = CustomOwner->GetMesh();
	if (!IsValid(mesh))
	{
		return;
	}

	TArray<AActor*> GetHitActors;
	if (!GetHitActors.Contains(CustomOwner))
	{
		GetHitActors.Add(CustomOwner);
	}

	UEveGameInstance* GameInstance = Cast<UEveGameInstance>(GetOwner()->GetGameInstance());
	if (!IsValid(GameInstance))
	{
		return;
	}
	FCharacterSkillTable* SkillInfo = GameInstance->GetSkillInfo(UnitType, SkillType, SkillIndex);
	if (SkillInfo == nullptr)
	{
		return;
	}

	switch (SkillInfo->SkillAreaType)
	{
	case EDamageAreaType::Area:
		DamageTriggerForAreaType(SkillInfo, SkillIndex, mesh, GetHitActors);
		break;
	case EDamageAreaType::SectorForm:
		DamageTriggerForSectorType(SkillInfo, SkillIndex, mesh, GetHitActors);
		break;
	}
}

bool UDamageComponent::DamageCalculate(USkeletalMeshComponent* _Mesh, const FCharacterSkillTable* SkillInfo, int Index, AEveCombatCharacter* AttackerChar,
									   AEveCombatCharacter* HitCharacter)
{
	float SkillMultiplier = SkillInfo->SkillIndexInfos[Index].DamageMultiplier;

	float delayTime = SkillInfo->HitRecoveryTime;
	float simulationSpeed = SkillInfo->HitDelaySpeed;

	//피격자 히트트리거
	bool HitMotion = SkillInfo->SkillIndexInfos[Index].HitValue > HitCharacter->GetHitRecovery();

	HitCharacter->HitTrigger(HitMotion);
	HitCharacter->HitSound();

	//피격자 경직
	HitCharacter->SetEffectSimulationSpeed(delayTime, simulationSpeed);
	HitCharacter->SetAniSpeed(delayTime, simulationSpeed);
	
	//데미지 계산 공식
	const float Damage = AttackerChar->GetStatComponent()->GetCurDamage();
	const int Armor = HitCharacter->GetStatComponent()->GetCurArmor();
	const float DamageMultiplier = Damage / (Damage + Armor);
	const int TotalDamage = static_cast<int>(Damage * DamageMultiplier * SkillMultiplier);
	auto DamageInfo = AEveStaticManager::DequeueDamageInfo();
	DamageInfo->Damage = -TotalDamage;
	int TotalCombatPoint = 0;
	if (AttackerChar->GetSideType() != EEveSideType::Enemy)
	{
		TotalCombatPoint = static_cast<int>(SkillInfo->SkillIndexInfos[Index].CombatPoint);
		DamageInfo->CombatGauge = -TotalCombatPoint;
	}
	
	HitCharacter->GetDamagePoint(DamageInfo);
	AttackerChar->OnHitPostTrigger.Broadcast(HitCharacter);

	
	if (AttackerChar->GetSideType() == EEveSideType::Player
		&& !IsValid(AttackerChar->GetTargetComponent()->GetTarget()))
	{
		// AttackerChar->GetTargetComponent()->SetTarget(HitCharacter);
		AttackerChar->ToggleTarget();
	}

	//로그
	Z_SCREEN_LOG(1, FColor::Cyan, TEXT("[%s]은 [%s]에게 [%d]의 데미지를 주었습니다."),
		*AttackerChar->GetName(),
		*HitCharacter->GetName(),
		TotalDamage);
	UE_LOG(LogTemp, Log, TEXT("%s가 %d 데미지와 %d 전투게이지를 %s에게 주었습니다. (남은체력: %d)(남은 게이지: %d)"),
		   *AttackerChar->GetName(),
		   TotalDamage,
		   TotalCombatPoint,
		   *HitCharacter->GetName(),
		   HitCharacter->GetHP(),
		   HitCharacter->GetCombatGauge());

	//데미지 폰트 표시
	// FJinDamageInfo DamageInfo;
	// DamageInfo.Damage = TotalDamage;
	// DamageInfo.DamageType = EJinDamageType::Normal;
	// AZRPGGameMode* GameMode =	 Cast<AZRPGGameMode>(UGameplayStatics::GetGameMode(this));
	// GameMode->ShowDamageNumber(DamageInfo, HitCharacter);
	FActorSpawnParameters Param;
	Param.Owner = HitCharacter;

	FVector DamageFontLocation;
	{
		const float Radius = 100.f;
		FVector RandForwrd = FMath::VRand();
		RandForwrd.Z = FMath::Abs(RandForwrd.Z);
		DamageFontLocation = HitCharacter->GetActorLocation() + RandForwrd * Radius;
	}
	AFloatingDamageActor* FloatingDamageActor = GetWorld()->SpawnActor<AFloatingDamageActor>(DamageFontLocation, FRotator::ZeroRotator, Param);
	if (IsValid(FloatingDamageActor))
	{
		FloatingDamageActor->Init(TotalDamage, FColor::Red);
	}

	return HitMotion;
}
