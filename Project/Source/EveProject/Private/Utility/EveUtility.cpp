// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/EveUtility.h"

#include "Kismet/GameplayStatics.h"
#include "Player/EvePlayerController.h"

void AEveUtility::CustomDrawDebugCapsuleBetweenPoints(UWorld* world, const FVector& Start, const FVector& End, float _Radius, const FColor& LineColor, EDrawDebugTrace::Type DrawDebugType)
{
	if (DrawDebugType == EDrawDebugTrace::None)
		return;

	const AEvePlayerController* PlayerController = Cast<AEvePlayerController>(UGameplayStatics::GetPlayerController(world, 0));
	if (!PlayerController->GetShowDebug())
		return;
	
	
	FVector MidPoint = (Start + End) * 0.5f; // 중간 지점 계산
	float DrawTime = 5.0f; // 선이 지속되는 시간 (초)
	bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
	float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

	uint8 DepthPriority = 0; // 그리기 깊이 우선순위 (기본값)
	float Thickness = 1.0f; // 선의 두께

	FVector const TraceVec = End - Start;
	float const Dist = TraceVec.Size();

	float HalfHeight = (Dist * 0.5f) + _Radius;

	FQuat const CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	DrawDebugCapsule(
	world,
	MidPoint,
	HalfHeight,
	_Radius,
	CapsuleRot,
	LineColor,
	bPersistent,
	LifeTime,
	DepthPriority,
	Thickness);
}

void AEveUtility::CustomDrawDebugLine(UWorld* world, const FVector& Start, const FVector& End, const FColor& LineColor,
	EDrawDebugTrace::Type DrawDebugType)
{
	if (DrawDebugType == EDrawDebugTrace::None)
		return;

	const AEvePlayerController* PlayerController = Cast<AEvePlayerController>(UGameplayStatics::GetPlayerController(world, 0));
	if (!PlayerController->GetShowDebug())
		return;

	float DrawTime = 5.0f; // 선이 지속되는 시간 (초)
	bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
	float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;
	uint8 DepthPriority = 0; // 그리기 깊이 우선순위 (기본값)
	float Thickness = 1.0f; // 선의 두께
	
	DrawDebugLine(world, Start, End, LineColor, bPersistent, LifeTime, DepthPriority, Thickness);
}

void AEveUtility::PrintToScreen(UWorld* world, FString YourMessage, FColor Color, float Duration)
{
	const AEvePlayerController* PlayerController = Cast<AEvePlayerController>(UGameplayStatics::GetPlayerController(world, 0));
	if (!PlayerController->GetShowDebug() )
		return;
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, YourMessage);
	}
}

