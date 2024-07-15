// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EveCharacter.h"

#include "NiagaraComponent.h"
#include "Animation/EveAnimInstance.h"
#include "Component/AIComponent.h"
#include "Component/EveAKComponent.h"
#include "Component/StateComponent.h"
#include "Component/TargetComponent.h"
#include "Component/BuffComponent.h"
#include "Data/FCharacterTable.h"
#include "Player/EvePlayerController.h"
#include "EveProject/EveProject.h"
#include "Game/EveBattleGameState.h"
#include "Game/EveGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AEveCharacter::AEveCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	TargetComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetComponent"));
	AKComponent = CreateDefaultSubobject<UEveAKComponent>(TEXT("AKComponent"));
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulaus"));
	if (StimuliSource)
	{
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSource->RegisterWithPerceptionSystem();
	}
	AIComponent = CreateDefaultSubobject<UAIComponent>(TEXT("AIComponent"));
	bIsServer = HasAuthority(); // 서버인 경우 true, 클라이언트인 경우 false
}

// Called when the game starts or when spawned
void AEveCharacter::BeginPlay()
{
	Super::BeginPlay();
	AEveBattleGameState* GameState = GetWorld()->GetGameState<AEveBattleGameState>();
	if (IsValid(GameState))
	{
		GameState->AddUnit(this);
		UE_LOG(LogTemp, Log, TEXT("%s이 생성되었습니다."), *GetName());
	}
	
	if (BaseMaterial)
	{
		DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);

		if (DynamicMaterialInstance)
		{
			// 특정 메쉬에 메테리얼 인스턴스 적용 (예: StaticMeshComponent)
			USkeletalMeshComponent* MeshComponent = FindComponentByClass<USkeletalMeshComponent>();
			if (MeshComponent)
			{
				MeshComponent->SetMaterial(0, DynamicMaterialInstance);
			}

			// 파라미터 값 설정
			DynamicMaterialInstance->SetScalarParameterValue(FName("EmissiveParam"), 0.0f);
		}
	}
}

void AEveCharacter::Init()
{	
	GameInstance = Cast<UEveGameInstance>(GetGameInstance());
	if (IsValid(GameInstance))
	{
		CurCharInfo = GameInstance->GetCharacterInfo(UnitType);
		if (CurCharInfo != nullptr)
		{
			StateComponent->SetCheckAbleToInputState(GameInstance->CheckAbleToInputState);
			StateComponent->SetCheckAbleToNormalAttackState(GameInstance->CheckAbleToInputNormalAttack);
			StateComponent->SetCheckAbleToMove(GameInstance->CheckAbleToMove);
			StateComponent->SetCheckAbleToHit(GameInstance->CheckAbleToHit);
		}
	}
	StateComponent->Reset();
	TargetComponent->Init();
	AnimInstance = Cast<UEveAnimInstance>(GetMesh()->GetAnimInstance());
}

void AEveCharacter::HideInTime(float DelayHideTime)
{
	TimeToHide = DelayHideTime;
	UseHideInTime = true;
	ResetAction();
}

void AEveCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEveCharacter, bIsServer);
}

// Called to bind functionality to input
void AEveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEveCharacter::CheckSetNewState(ECharState NewState)
{
	if (!StateComponent->AbleToInput(NewState))
		return;

	switch (NewState)
	{
	case ECharState::None:
		break;
	case ECharState::Idle:
		break;
	case ECharState::Jumping:
		break;
	case ECharState::Dash:
		// TriggerDash();
		break;
	default: ;
	}
}

void AEveCharacter::SetAnimation(ECharState NewState, ECharAction NewAction)
{	
	switch (NewState)
	{
	case ECharState::None:
		break;
	case ECharState::Idle:
		break;
	case ECharState::Death:
		break;
	case ECharState::Jumping:
	case ECharState::Dash:
	case ECharState::Skill1:
	case ECharState::UltimateSkill:
		AnimInstance->Montage_Play(CurSkillInfo->SkillMontage);
		break;
	default: ;
	}
}

bool AEveCharacter::SetSkillInfo(ECharState NewState, ECharAction NewAction)
{
	// CurSkillInfo = GameInstance->GetSkillInfo(UnitType, ESkillType::NormalAttack01);
	return true;
}

void AEveCharacter::TriggerDash()
{
	//Dash 가능한지 체크
	const FVector DesiredForwardVector = GetMovementComponent()->GetLastInputVector();
	const double Squared = DesiredForwardVector.SizeSquared();
	if (Squared > 0.15f)
	{
		ServerSetNewState(ECharState::Dash, ECharAction::Dash);
		SetNewState(ECharState::Dash, ECharAction::Dash);
	}
	else
	{
		ServerSetNewState(ECharState::Dash, ECharAction::BackDash);
		SetNewState(ECharState::Dash, ECharAction::BackDash);
	}
}

void AEveCharacter::SetForceNewState(ECharState NewState, ECharAction NewAction)
{
	if (!SetSkillInfo(NewState, NewAction))
		return;
	ResetCurveMove();
	if (StateComponent->SetState(NewState, true)
		&& StateComponent->SetAction(NewAction, true))
	{
		if (CurSkillInfo != nullptr && CurSkillInfo->UseMoveCurve)
			UseCurveMove = true;
		SetAnimation(NewState, NewAction);
	}
}

void AEveCharacter::ServerSetForceNewState_Implementation(ECharState NewState, ECharAction NewAction)
{
	MulticastSetForceNewState(NewState, NewAction);
}

void AEveCharacter::MulticastSetForceNewState_Implementation(ECharState NewState, ECharAction NewAction)
{
	if (!CheckController())
	{
		SetForceNewState(NewState, NewAction);
	}
}

void AEveCharacter::ResetCurveMove()
{
	UseCurveMove = false;
}

void AEveCharacter::AddNiagaraEffect(UNiagaraComponent* NiagaraComponent)
{
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AEveCharacter::OnNiagaraSystemFinished);
	NiagaraComponents.Add(NiagaraComponent);
}

void AEveCharacter::OnNiagaraSystemFinished(UNiagaraComponent* PSystem)
{
	NiagaraComponents.Remove(PSystem);
}

void AEveCharacter::SetNewState(ECharState NewState, ECharAction NewAction)
{
	if (!SetSkillInfo(NewState, NewAction))
		return;
	ResetCurveMove();
	if (StateComponent->SetState(NewState)
		&& StateComponent->SetAction(NewAction))
	{
		if (CurSkillInfo != nullptr && CurSkillInfo->UseMoveCurve)
			UseCurveMove = true;
		SetAnimation(NewState, NewAction);
	}
}


void AEveCharacter::ServerSetNewState_Implementation(ECharState NewState, ECharAction NewAction)
{
	MulticastSetNewState(NewState, NewAction);
}

void AEveCharacter::MulticastSetNewState_Implementation(ECharState NewState, ECharAction NewAction)
{
	if (!CheckController())
	{
		SetNewState(NewState, NewAction);
	}
}

void AEveCharacter::ResetAction()
{
	ResetCurveMove();
	StateComponent->Reset();
}

void AEveCharacter::SetNewAction(ECharAction NewAction)
{
	if (!SetSkillInfo(StateComponent->GetCurrentState(), NewAction))
		return;
	ResetCurveMove();
	if (StateComponent->SetAction(NewAction))
	{
		if (CurSkillInfo != nullptr && CurSkillInfo->UseMoveCurve)
			UseCurveMove = true;
		SetAnimation(StateComponent->GetCurrentState(), NewAction);
	}
}

bool AEveCharacter::CheckController()
{
	return IsLocallyControlled() || OwnerController == GetWorld()->GetFirstPlayerController();
}

void AEveCharacter::MulticastSetNewAction_Implementation(ECharAction NewAction)
{
	MulticastSetNewAction(NewAction);
}

void AEveCharacter::ServerSetNewAction_Implementation(ECharAction NewAction)
{
	if (!IsLocallyControlled())
	{
		SetNewAction(NewAction);
	}
}
