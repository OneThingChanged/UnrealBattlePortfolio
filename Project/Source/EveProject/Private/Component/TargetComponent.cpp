// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/TargetComponent.h"

#include "KismetTraceUtils.h"
#include "Camera/EveCameraComponent.h"
#include "Character/EveCombatCharacter.h"
#include "Component/StatComponent.h"
#include "Game/EveBattleGameState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widget/BattleEnemyWidget.h"
#include "Utility/EveUtility.h"


class UCameraComponent;
// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTargetComponent::Init()
{
	CustomOwner = Cast<AEveCombatCharacter>(GetOwner());
	if (!IsValid(CustomOwner))
		return;
	HasTarget = false;
	IgnoreUpdate = true;
	OwnerController = CustomOwner->GetController();
	SetRotationMode(EEveCameraRotationMode::DirectToMovement);
}

void UTargetComponent::UpdateTargetControlRotation()
{
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("(%s)UpdateTargetControlRotation: Missing Target"), *GetOwner()->GetName());
		DisableLockOn();
		return;
	}
	if (!HasTarget)
	{
		return;
	}

	if (OwnerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("(%s)UpdateTargetControlRotation: Missing OwnerController"), *GetOwner()->GetName());
		if (CustomOwner == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("(%s)UpdateTargetControlRotation: Missing OwnerCharacter"), *GetOwner()->GetName());
			DisableLockOn();
			return;
		}
		OwnerController = CustomOwner->GetController();
		if (OwnerController == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("(%s)UpdateTargetControlRotation: Missing OwnerController"), *GetOwner()->GetName());
			DisableLockOn();
			return;
		}
	}
}

void UTargetComponent::EnableLockOn()
{
	UE_LOG(LogTemp, Error, TEXT("Enable Target Name: %s"), *GetOwner()->GetName() );
	// if (FindTarget())
	// {
	// 	IgnoreUpdate = false;
	// 	SetHasTarget(true);
	// 	SetRotationMode(DefaultRotationMode);
	// 	// if (Target->AbleToTarget())
	// 	// {
	// 	// 	Target->SetTarget(true);
	// 	// }
	// }
}

void UTargetComponent::DisableLockOn()
{
	UE_LOG(LogTemp, Error, TEXT("Disable Target Name: %s"), *GetOwner()->GetName() );
	// if (Target != nullptr)
	// {
	// 	Target->SetTarget();
	// }
	//
	// IgnoreUpdate = true;
	// SetHasTarget(false);
	// SetRotationMode(EEveCameraRotationMode::DirectToMovement);
	// GetOwner()->GetWorldTimerManager().ClearTimer(InputDelayTimer);
}

void UTargetComponent::NoneTarget()
{
	if (IsValid(Target))
	{
		Target->GetTargetComponent()->DisableLockOn();
	}
	CurRotationMode = EEveCameraRotationMode::DirectToMovement;
	Target = nullptr;
	HasTarget = false;
	IgnoreUpdate = true;
}


// Called every frame
void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IgnoreUpdate)
	{
		return;
	}
	// UpdateTargetControlRotation();
	return;
	// if (!HasTarget || !IsValid(Target))
	// {
	// 	NoneTarget();
	// 	return;
	// }
	//
	// FVector TargetLocation = Target->GetActorLocation();
	// FVector OwnerLocation = CustomOwner->GetActorLocation();
	// float Distance = (TargetLocation - OwnerLocation).Size();
	// // if (!Target->AbleToTarget() || Distance > SearchRadius)
	// if (Distance > Radius)
	// {
	// 	NoneTarget();
	// 	return;
	// }
	//
	// TargetLocation -= ControlCameraView;
	// FRotator TargetDesiredRotation = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);
	// AController* Controller = CustomOwner->GetController();
	// FRotator ControllerRotation =Controller->GetControlRotation();
	// if (CurRotationMode == EEveCameraRotationMode::OrientToCamera)
	// {
	// 	FRotator InterpRotation = UKismetMathLibrary::RInterpTo(ControllerRotation, TargetDesiredRotation, GetWorld()->GetDeltaSeconds(), TargetRotationInterpSpeed);
	// 	InterpRotation.Roll = ControllerRotation.Roll;
	// 	InterpRotation.Pitch += CameraPitchWhenTarget;
	// 	Controller->SetControlRotation(InterpRotation);
	// }
	// else
	// {
	// 	TargetDesiredRotation.Roll = ControllerRotation.Roll;
	// 	TargetDesiredRotation.Pitch = CameraPitchWhenTarget;
	// 	Controller->SetControlRotation(TargetDesiredRotation);
	// }
}

AEveCombatCharacter* UTargetComponent::FindTargetInSector() const
{
	TArray<FOverlapResult> OverlappingActors;

	FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	TArray<AActor*> GetHitActors;
	if (!GetHitActors.Contains(GetOwner()))
	{
		GetHitActors.Add(GetOwner());
	}
	
	// 무기의 소유자를 Ignore Actors 배열에 추가합니다.
	TraceParams.AddIgnoredActors(GetHitActors);

	// Sphere 중심에서의 위치
	FVector SphereCenter = CustomOwner->GetActorLocation();
	
	bool bHit = GetWorld()->OverlapMultiByObjectType(
			OverlappingActors,
			SphereCenter,
			FQuat::Identity,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
			FCollisionShape::MakeSphere(Radius),
			TraceParams
		);

	if (!bHit)
	{
		AEveUtility::CustomDrawDebugCapsuleBetweenPoints(GetWorld(), SphereCenter, SphereCenter, Radius,
														 FColor::Red, DebugType);
		return nullptr;
	}

	// Sphere 중심에서의 방향 벡터
	FVector SphereForwardVector = CustomOwner->GetActorForwardVector();

	// 내 앞의 좌우 30도 이내에 있는 적을 찾는 각도 (cosine 값 사용)
	float CosineThreshold = FMath::Cos(FMath::DegreesToRadians(Degree));
	float DistanceBetweenTarget = Radius;
	AEveCombatCharacter* NewTarget = nullptr;
	FVector OwnerLocation = CustomOwner->GetActorLocation();
	for (const FOverlapResult& HitResult : OverlappingActors)
	{
		AActor* HitActor = HitResult.GetActor();
		AEveCombatCharacter* HitCharacter = Cast<AEveCombatCharacter>(HitActor);
		if (!IsValid(HitActor)
			|| !IsValid(HitCharacter))
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

		
			auto TempDistance = FVector::Distance(OwnerLocation, EnemyLocation);
			if (DistanceBetweenTarget > TempDistance)
			{
				NewTarget = HitCharacter;
				DistanceBetweenTarget = TempDistance;
			}
		}
		else
		{
			AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, EnemyLocation, FColor::Red, DebugType);
		}
	}

	if (IsValid(NewTarget))
	{
		// 캐릭터의 위치
		FVector CharacterLocation = CustomOwner->GetActorLocation();

		// 캐릭터의 시야 방향 벡터
		FVector ViewDirection = CustomOwner->GetActorForwardVector();

		// 시야 방향의 회전을 얻음
		FRotator ViewRotation = CustomOwner->GetActorRotation();

		// 좌우 n도 회전값 계산
		FRotator LeftRotation = ViewRotation + FRotator(0, -Degree, 0);
		FRotator RightRotation = ViewRotation + FRotator(0, Degree, 0);

		// 좌우 n도 방향 벡터 계산
		FVector LeftDirection = LeftRotation.Vector();
		FVector RightDirection = RightRotation.Vector();

		// 좌측과 우측 방향으로 길이 radius 만큼 이동한 좌표 계산
		FVector LeftPoint = CharacterLocation + LeftDirection * Radius;
		FVector RightPoint = CharacterLocation + RightDirection * Radius;

		AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, LeftPoint, FColor::Blue, DebugType);
		AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, RightPoint, FColor::Blue, DebugType);
		AEveUtility::CustomDrawDebugCapsuleBetweenPoints(GetWorld(), SphereCenter, SphereCenter, Radius,
														 FColor::Green, DebugType);
		AEveUtility::CustomDrawDebugLine(GetWorld(), SphereCenter, NewTarget->GetActorLocation(), FColor::Green, DebugType);
	}
	else
	{
		AEveUtility::CustomDrawDebugCapsuleBetweenPoints(GetWorld(), SphereCenter, SphereCenter, Radius,
												 FColor::Red, DebugType);
	}
	
	return NewTarget;
}

void UTargetComponent::SetHasTarget(bool bCond)
{
	HasTarget = bCond;
}
void UTargetComponent::SetRotationMode(EEveCameraRotationMode _RotationMode)
{
	CurRotationMode = _RotationMode;
}

void UTargetComponent::SetTarget(AEveCombatCharacter* NewTarget)
{
	Target = NewTarget;
	IgnoreUpdate = false;
	SetHasTarget(true);
	SetRotationMode(DefaultRotationMode);
	Target->SetTarget();
}

bool UTargetComponent::FindTarget()
{
	//새로운 타겟 찾기
	auto NewTarget = FindTargetInSector();
	if (IsValid(NewTarget) && NewTarget != Target)
	{
		SetTarget(Target);
		return true;
	}
	else
	{
		NoneTarget();
		return false;
	}
}


void UTargetComponent::InactiveTargetUI()
{
	AEveBattleGameState* GameState = GetWorld()->GetGameState<AEveBattleGameState>();
	if (IsValid(GameState))
	{
		GameState->EnemyWidget->ShowUI(false);
		Target->OnDrawUITrigger.RemoveDynamic(GameState->EnemyWidget, &UBattleEnemyWidget::SetHPProgressBar);
		Target->OnDrawUITrigger.RemoveDynamic(GameState->EnemyWidget, &UBattleEnemyWidget::SetCombatProgressBar);
		Target->OnCharDeathTrigger.RemoveDynamic(GameState->EnemyWidget, &UBattleEnemyWidget::DeathTrigger);
		Target->OnDeathTrigger.RemoveDynamic(this, &UTargetComponent::NoneTarget);
	}
	NoneTarget();
}

void UTargetComponent::ActiveTargetUI()
{	
	AEveBattleGameState* GameState = GetWorld()->GetGameState<AEveBattleGameState>();
	if (IsValid(GameState))
	{
		GameState->EnemyWidget->ShowUI(true);
		auto CharInfo = Target->GetStatComponent()->GetStatInfo();
		GameState->EnemyWidget->SetHPProgressBar(CharInfo);
		GameState->EnemyWidget->SetCombatProgressBar(CharInfo);
		Target->OnDrawUITrigger.AddDynamic(GameState->EnemyWidget, &UBattleEnemyWidget::SetHPProgressBar);
		Target->OnDrawUITrigger.AddDynamic(GameState->EnemyWidget, &UBattleEnemyWidget::SetCombatProgressBar);
		Target->OnCharDeathTrigger.AddDynamic(GameState->EnemyWidget, &UBattleEnemyWidget::DeathTrigger);
		Target->OnDeathTrigger.AddDynamic(this, &UTargetComponent::NoneTarget);
	}
}

void UTargetComponent::SetPlayable()
{
	
	// 플레이어 캐릭터에 카메라를 부착하기 위해 SpringArm 및 카메라 생성
	SpringArm = NewObject<USpringArmComponent>(this, TEXT("SpringArm"));
	Camera = NewObject<UEveCameraComponent>(this, TEXT("Camera"));

	// SpringArm 설정
	SpringArm->SetupAttachment(GetOwner()->GetRootComponent()); // 플레이어 캐릭터의 루트 컴포넌트에 부착
	SpringArm->TargetArmLength = 400; // 카메라와의 거리 (원하는 값으로 변경)
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 60)); // SpringArm 위치 설정
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true; // 카메라 랙 설정

	// 카메라 설정
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // SpringArm에 부착
	Camera->bUsePawnControlRotation = true; // 캐릭터의 회전과 함께 카메라가 회전하도록 설정

	// SpringArm과 카메라를 플레이어 캐릭터에 추가
	SpringArm->RegisterComponent();
	Camera->RegisterComponent();
}

void UTargetComponent::SetSpringArmLength(float Length)
{
	SpringArm->TargetArmLength = Length;
}

void UTargetComponent::SetCameraLocation(FVector Location)
{
	SpringArm->SetRelativeLocation(Location); // SpringArm 위치 설정
}

void UTargetComponent::ToggleTarget()
{
	if (IsValid(Target))
	{
		InactiveTargetUI();
	}
	else
	{
		auto NewTarget = FindTargetInSector();
		if (IsValid(NewTarget))
		{
			SetTarget(NewTarget);
			ActiveTargetUI();
		}
	}
}