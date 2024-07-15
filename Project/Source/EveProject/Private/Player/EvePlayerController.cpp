// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EvePlayerController.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Character/EveCharacter.h"
#include "Character/EveCombatCharacter.h"
#include "Component/StatComponent.h"
#include "Component/StateComponent.h"
#include "Component/TargetComponent.h"
#include "CustomClass/InfoClass/EveSkillInfo.h"
#include "EveProject/EveProject.h"
#include "Game/EveBattleGameMode.h"
#include "Game/EveBattleGameState.h"
#include "GameFramework/GameUserSettings.h"
#include "GameFramework/PlayerStart.h"
#include "HUD/BattleHUD.h"
#include "Manager/EveCheatManager.h"
#include "UI/Widget/BattleEnemyWidget.h"
#include "UI/Widget/BattlePlayerWidget.h"
#include "UI/Widget/BattleSkillButtonWidget.h"

AEvePlayerController::AEvePlayerController()
{
	bReplicates = true;
	CheatClass = UEveCheatManager::StaticClass();
}

void AEvePlayerController::HitCount(AEveCombatCharacter* HitCharacter)
{
	ComboCount++;
	int32 DisplayedCombo = ComboCount + AdditionalHitCount;
	DisplayedCombo = FMath::Clamp(DisplayedCombo, 0, DisplayedCombo);
	GetWorld()->GetGameState<AEveBattleGameState>()->PlayerWidget->SetCombo(DisplayedCombo);

	// auto CurTarget = CurCharacter->GetTargetComponent()->GetTarget();
	// if (!IsValid(CurTarget) && HitCharacter->IsAbleToTarget())
	// {
	// 	CurCharacter->GetTargetComponent()->SetTarget(HitCharacter);
	// 	CurCharacter->GetTargetComponent()->ActiveTargetUI();
	// }

}

bool AEvePlayerController::GetHitCount(int RequestComboCount)
{
	if (ComboCount >= RequestComboCount)
	{
		ComboCount -= RequestComboCount;
		GetWorld()->GetGameState<AEveBattleGameState>()->PlayerWidget->SetCombo(ComboCount);
		return true;
	}
	return false;
}

void AEvePlayerController::SetAdditionalHitCount(int32 InAdditionalHitCount)
{
	AdditionalHitCount = InAdditionalHitCount;
}

int32 AEvePlayerController::GetAdditionalHitCount() const
{
	return AdditionalHitCount;
}

void AEvePlayerController::SetUI()
{
	AEveBattleGameState* EveGameState = GetWorld()->GetGameState<AEveBattleGameState>();
	UBattlePlayerWidget* PlayerWidget = EveGameState->PlayerWidget;

	//Player Charcter
	auto PlayerSkillInfo = CurCharacter->GetCombatComponent()->GetSkillInfos();
	PlayerSkillInfo[ESkillType::Skill1]->FOnSkillTickAction.AddDynamic(
		PlayerWidget->W_Skill1Button, &UBattleSkillButtonWidget::TickUI);

	PlayerSkillInfo[ESkillType::Skill1]->FOnSetAbleToUseSkillAction.AddDynamic(
		PlayerWidget->W_Skill1Button, &UBattleSkillButtonWidget::ActiveButton);
	
	PlayerSkillInfo[ESkillType::UltimateSkill]->FOnSkillTickAction.AddDynamic(PlayerWidget->W_UltimateButton, &UBattleSkillButtonWidget::TickUI);

	PlayerSkillInfo[ESkillType::UltimateSkill]->FOnSetAbleToUseSkillAction.AddDynamic(PlayerWidget->W_UltimateButton, &UBattleSkillButtonWidget::ActiveButton);

	CurCharacter->GetStateComponent()->OnStateEnd.AddDynamic(PlayerWidget, &UBattlePlayerWidget::UseSkillEnd);

	UEveGameInstance* GameInstance = Cast<UEveGameInstance>(GetGameInstance());
	EEveUnitType UnitType = CurCharacter->GetUnitType();
	TMap<ESkillType, UEveSkillInfo*> SkillInfos = CurCharacter->GetCombatComponent()->GetSkillInfos();
	
	PlayerWidget->W_NormalAttackButton->SetSkillImage(GameInstance->GetSkillInfo(UnitType, ESkillType::NormalAttack01)->ImageIcon);
	PlayerWidget->W_UltimateButton->SetSkillImage(GameInstance->GetSkillInfo(UnitType, ESkillType::UltimateSkill)->ImageIcon);
	PlayerWidget->W_Skill1Button->SetSkillImage(GameInstance->GetSkillInfo(UnitType, ESkillType::Skill1)->ImageIcon);

	CurCharacter->OnDrawUITrigger.AddDynamic(PlayerWidget, &UBattlePlayerWidget::UpdatePlayerCharacterUI);
	CurCharacter->OnHitPostTrigger.AddDynamic(this, &AEvePlayerController::HitCount);

	PlayerWidget->UpdatePlayerCharacterUI(CurCharacter->GetStatComponent()->GetStatInfo());
	PlayerWidget->SetPlayerCharacterUI(CurCharacter->GetCharInfo());
	

	for (int i = 0; i < 3; ++i)
	{
		PlayerWidget->SupportCharButtons[i]->SetVisibility(ESlateVisibility::Collapsed);
		continue;
		// if (SupportCharacters.Num() <= i)
		// {
		// 	PlayerWidget->SupportCharButtons[i]->SetVisibility(ESlateVisibility::Collapsed);
		// 	continue;
		// }
		//
		// EEveUnitType SupportUnitType =  SupportCharacters[i]->GetUnitType();
		// auto SupportCharSkill = SupportCharacters[i]->GetCombatComponent()->GetSkillInfos();
		// PlayerWidget->SupportCharButtons[i]->W_CharUltimateButton->SetSkillImage(GameInstance->GetSkillInfo(SupportUnitType, ESkillType::UltimateSkill)->ImageIcon);
		// SupportCharSkill[ESkillType::UltimateSkill]->FOnSkillTickAction.AddDynamic(
		// 	PlayerWidget->SupportCharButtons[i]->W_CharUltimateButton, &UBattleSkillButtonWidget::TickUI);
		// SupportCharSkill[ESkillType::UltimateSkill]->FOnSetAbleToUseSkillAction.AddDynamic(
		// 	PlayerWidget->SupportCharButtons[i]->W_CharUltimateButton, &UBattleSkillButtonWidget::ActiveButton);
		//
		// PlayerWidget->SupportCharButtons[i]->W_CharSkillButton->SetSkillImage(GameInstance->GetSkillInfo(SupportUnitType, ESkillType::Skill1)->ImageIcon);
		// SupportCharSkill[ESkillType::Skill1]->FOnSkillTickAction.AddDynamic(
		// 	PlayerWidget->SupportCharButtons[i]->W_CharSkillButton, &UBattleSkillButtonWidget::TickUI);
		// SupportCharSkill[ESkillType::Skill1]->FOnSetAbleToUseSkillAction.AddDynamic(
		// 	PlayerWidget->SupportCharButtons[i]->W_CharSkillButton, &UBattleSkillButtonWidget::ActiveButton);
		//
		// SupportCharacters[i]->GetStateComponent()->OnStateEnd.AddDynamic(PlayerWidget->SupportCharButtons[i], &UBattleCharButtonWidget::UseSkillEnd);
	}
}

void AEvePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputContext);
	UE_LOG(LogTemp, Log, TEXT("PlayerController"));
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	// check(Subsystem);
	if (Subsystem)
		Subsystem->AddMappingContext(InputContext, 0);

	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	UserSettings->bUseVSync = true;

	bShowMouseCursor = false;

	APlayerStart* PlayerStart = nullptr;
	for (const auto& TempPlayerStart : TActorRange<APlayerStart>(GetWorld()))
	{
		if (IsValid(TempPlayerStart))
			PlayerStart = TempPlayerStart;
		break;
	}
	if (!IsValid(PlayerStart))
		return;
	FVector TempSpawnLocation = PlayerStart->GetActorLocation();
	FRotator TempSpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	//게임 스테이트 생성
	GetWorld()->SpawnActor<ABattleHUD>(BattleHUD, TempSpawnLocation, TempSpawnRotation);
	UE_LOG(LogTemp, Log, TEXT("HUDFromPlayerController"));
	AEveBattleGameMode* GameMode = Cast<AEveBattleGameMode>(GetWorld()->GetAuthGameMode());
	TSubclassOf<AEveCombatCharacter> CharacterClass = GameMode->PlayerCharacter;
	
	CurCharacter = GetWorld()->SpawnActor<AEveCombatCharacter>(CharacterClass, TempSpawnLocation, TempSpawnRotation);
	if (CurCharacter->GetUnitType() == EEveUnitType::None)
		return;
	
	Possess(CurCharacter);
	CurCharacter->SetPlayable();
	UE_LOG(LogTemp, Log, TEXT("CharacterFromPlayerController"));
	CurCharacter->Init();


	for (auto SupportCharClass : GameMode->SupportChar)
	{
		AEveCombatCharacter* SupportCharacter = GetWorld()->SpawnActor<AEveCombatCharacter>(SupportCharClass, TempSpawnLocation, TempSpawnRotation);
		SupportCharacter->SetSupport();
		SupportCharacter->Init();
		SupportCharacter->SetOwnerController(this);
		SupportCharacter->GetMesh()->SetVisibility(false);
		SupportCharacters.Add(SupportCharacter);
	}

	SetUI();
	// FVector TempSpawnLocation = PlayerStart->GetActorLocation();
	// FRotator TempSpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	// //게임 인스턴스 활성화
	// UJinGameInstance* GameInstance = Cast<UJinGameInstance>(GetGameInstance());
	//
	// if (GameInstance)
	// {
	// // GameInstance 초기화 작업을 수행합니다.
	// 	GameInstance->CustomInit();
	// }
	//
	// // 시작 시 3개의 캐릭터 생성
	// for	(int i = 0; i < SpawnCharactersList.Num(); i++)
	// {
	// 	TSubclassOf<AJinCombatChar> CharacterClass = SpawnCharactersList[i];
	// 	TempSpawnLocation += FVector(100.0f * i, 0.0f, 0.0f);
	// 	
	// 	// FTransform SpawnTransform = GetWorld() GetActorTransform(); // 스폰 위치 및 회전 설정
	// 	AJinCombatChar* NewCharacter = GetWorld()->SpawnActor<AJinCombatChar>(CharacterClass, TempSpawnLocation, TempSpawnRotation);
	//
	// 	if (NewCharacter == nullptr)
	// 		continue;
	//
	// 	// 인덱스가 0 이상이면 숨김
	// 	if (i > 0)
	// 	{
	// 		NewCharacter->SetHiddenInGame(true);
	// 	}
	// 	else
	// 	{
	// 		ActiveCharacter = NewCharacter;
	// 		ActiveCharacter->SetHiddenInGame(false);
	// 		Possess(ActiveCharacter);
	// 	}
	//
	// 	// 생성된 캐릭터를 배열에 추가
	// 	PlayerCharacters.Add(NewCharacter);
	// }

	// OnChangeCharacterEvent.Broadcast();
	// OnChangeCharacterParamEvent.Broadcast(ActiveCharacter);
}

void AEvePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (IsValid(CurCharacter))
	{
		
		float Speed = CameraOffsetCurve->GetFloatValue(CurCharacter->GetTargetComponent()->GetSpringArmLength() / (MaxSpringArmLength - minSpringArmLength));
		CurCharacter->GetTargetComponent()->SetCameraLocation(FVector(0,0,Speed));
	}
}

void AEvePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
			&AEvePlayerController::Jump);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
			&AEvePlayerController::StopJumping);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this,
		                                   &AEvePlayerController::StartSprint);
		
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Ongoing, this,
		                                   &AEvePlayerController::OnGoingSprint);
		
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this,
		                                   &AEvePlayerController::EndSprint);

		//Skill
		EnhancedInputComponent->BindAction(UltimateSkillAction, ETriggerEvent::Started, this,
		                                   &AEvePlayerController::UltimateStart);
		
		EnhancedInputComponent->BindAction(UltimateSkillAction, ETriggerEvent::Completed, this,
		                                   &AEvePlayerController::UltimateEnd);
		
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Started, this,
		                                   &AEvePlayerController::NormalAttackStart);
		
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Triggered, this,
		                                   &AEvePlayerController::NormalAttackTrigger);
		
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Ongoing, this,
		                                   &AEvePlayerController::NormalAttackOnGoing);
		
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Completed, this,
		                                   &AEvePlayerController::NormalAttackEnd);
		
		EnhancedInputComponent->BindAction(Skill1Action, ETriggerEvent::Started, this,
		                                   &AEvePlayerController::Skill1Start);
		
		//회피
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this,
											&AEvePlayerController::Dodge);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
											&AEvePlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
											&AEvePlayerController::Look);

		// ToggleTarget
		EnhancedInputComponent->BindAction(ToggleTargetAction, ETriggerEvent::Started, this,
											&AEvePlayerController::ToggleTarget);

		// ShowPointer
		EnhancedInputComponent->BindAction(ShowPointerAction, ETriggerEvent::Started, this,
											&AEvePlayerController::ShowPointer);
		
		EnhancedInputComponent->BindAction(ShowPointerAction, ETriggerEvent::Completed, this,
											&AEvePlayerController::HidePointer);

		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this,
											&AEvePlayerController::SetSpringArmLength);

		//Support
		EnhancedInputComponent->BindAction(UseChar1Skill, ETriggerEvent::Started, this,
											&AEvePlayerController::Char1Skill);

		EnhancedInputComponent->BindAction(UseChar2Skill, ETriggerEvent::Started, this,
											&AEvePlayerController::Char2Skill);

		EnhancedInputComponent->BindAction(UseChar3Skill, ETriggerEvent::Started, this,
											&AEvePlayerController::Char3Skill);

		EnhancedInputComponent->BindAction(TriggerAction, ETriggerEvent::Started, this,
									&AEvePlayerController::StartTriggerButton);
		
		EnhancedInputComponent->BindAction(TriggerAction, ETriggerEvent::Completed, this,
							&AEvePlayerController::EndTriggerButton);
	}
	else
	{
		UE_LOG(LogTemp, Error,
		       TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void AEvePlayerController::ShowDebugScreen()
{
	ShowDebug = !ShowDebug;
}

void AEvePlayerController::Jump(const FInputActionValue& Value)
{
	if (AEveCharacter* ControlledCharacter = GetPawn<AEveCharacter>())
	{
		// ControlledCharacter->StartJump();
		ControlledCharacter->bPressedJump = true;
		ControlledCharacter->JumpKeyHoldTime = 0.0f;
	}
}

void AEvePlayerController::StopJumping(const FInputActionValue& Value)
{
	if (AEveCharacter* ControlledCharacter = GetPawn<AEveCharacter>())
	{
		ControlledCharacter->bPressedJump = false;
		ControlledCharacter->ResetJumpState();
	}
}

void AEvePlayerController::StartSprint(const FInputActionValue& Value)
{
	// if (AEveCharacter* ControlledCharacter = GetPawn<AEveCharacter>())
	// {
	// 	ControlledCharacter->StartSprint();
	// }
}

void AEvePlayerController::OnGoingSprint(const FInputActionInstance& Value)
{
	// if (AEveCharacter* ControlledCharacter = GetPawn<AEveCharacter>())
	// {		
	// 	ControlledCharacter->OnGoingSprint(Value.GetElapsedTime());
	// }
}

void AEvePlayerController::EndSprint(const FInputActionValue& Value)
{
	// if (AEveCharacter* ControlledCharacter = GetPawn<AEveCharacter>())
	// {
	// 	ControlledCharacter->EndSprint();
	// }
}

void AEvePlayerController::StartTriggerButton(const FInputActionValue& Value)
{
	OnTriggerAction = true;
}

void AEvePlayerController::EndTriggerButton(const FInputActionValue& Value)
{
	OnTriggerAction = false;
}

void AEvePlayerController::Move(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn<APawn>();
	if (!IsValid(ControlledPawn))
		return;

	AEveCharacter* EveChar = Cast<AEveCharacter>(ControlledPawn);
	if (!IsValid(EveChar) || !EveChar->GetStateComponent()->AbleToMove())
		return;

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	const FVector2D MovementVector = Value.Get<FVector2D>();

	// UE_LOG(LogUnitLogic, Log, TEXT("MyVector: %s %s"), *Rotation.ToString(), *Rotation1.ToString());
	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
}

void AEvePlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		// ControlledPawn->TargetComponent->StopTargetingForWhile();
	}
}

void AEvePlayerController::Dodge(const FInputActionValue& Value)
{
	if (AEveCombatCharacter* ControlledCharacter = GetPawn<AEveCombatCharacter>())
	{
		ControlledCharacter->InputDashStart();
	}
}

void AEvePlayerController::ToggleTarget(const FInputActionValue& Value)
{
	// UE_LOG(LogTemp, Log, TEXT("Start"));
	if (AEveCombatCharacter* ControlledCharacter = GetPawn<AEveCombatCharacter>())
	{
		ControlledCharacter->ToggleTarget();
	}
}

void AEvePlayerController::NormalAttackStart()
{
	if (AEveCombatCharacter* ControlledCharacter = GetPawn<AEveCombatCharacter>())
	{
		ControlledCharacter->InputNormalAttackStart();
		// ControlledCharacter->InputSkill1Start();
	}
}

void AEvePlayerController::HidePointer()
{
	bShowMouseCursor = false;
	// bEnableClickEvents = false;
	// bEnableMouseOverEvents = false;
}

void AEvePlayerController::ShowPointer()
{
	bShowMouseCursor = true;
	// bEnableClickEvents = true;
	// bEnableMouseOverEvents = true;
}

void AEvePlayerController::CharUltimateSkillStart(int Index)
{
	SupportCharUltimateSkill(Index);
}

void AEvePlayerController::CharActiveSkillStart(int Index)
{
	SupportCharActiveSkill(Index);
}

void AEvePlayerController::SetSpringArmLength(const FInputActionValue& Value)
{
	const float MovementVector = Value.Get<float>();
	auto temp = CurCharacter->GetTargetComponent()->GetSpringArmLength();
	temp += DifferArmLength * MovementVector;
	if (temp > MaxSpringArmLength)
	{
		temp = MaxSpringArmLength;
	}else if (temp < minSpringArmLength)
	{
		temp = minSpringArmLength;
	}
	CurCharacter->GetTargetComponent()->SetSpringArmLength(temp);
}

void AEvePlayerController::SetCameraLocation()
{
}

void AEvePlayerController::NormalAttackTrigger(const FInputActionInstance& Value)
{
	// UE_LOG(LogTemp, Log, TEXT("Trigger"));
}

void AEvePlayerController::NormalAttackOnGoing(const FInputActionInstance& Value)
{
	// UE_LOG(LogTemp, Log, TEXT("Ongoing"));
	// if (AEveCombatCharacter* ControlledCharacter = GetPawn<AEveCombatCharacter>())
	// {
	// 	ControlledCharacter->InputNormalChargeAttack(Value.GetElapsedTime());
	// }
}

void AEvePlayerController::NormalAttackEnd(const FInputActionInstance& Value)
{
	// UE_LOG(LogTemp, Log, TEXT("End"));
}

void AEvePlayerController::Skill1Start()
{
	AEveCombatCharacter* ControlledCharacter = GetPawn<AEveCombatCharacter>();
	if (IsValid(ControlledCharacter))
	{
		ControlledCharacter->InputSkill1Start();
	}
}

void AEvePlayerController::Skill1End(const FInputActionValue& Value)
{
}

void AEvePlayerController::Skill2Start(const FInputActionValue& Value)
{
}

void AEvePlayerController::Skill2End(const FInputActionValue& Value)
{
}

void AEvePlayerController::Skill3Start(const FInputActionValue& Value)
{
}

void AEvePlayerController::Skill3End(const FInputActionValue& Value)
{
}

void AEvePlayerController::UltimateStart()
{
	if (AEveCombatCharacter* ControlledCharacter = GetPawn<AEveCombatCharacter>())
	{
		ControlledCharacter->InputUltimateSkillStart();
	}
}

void AEvePlayerController::UltimateEnd(const FInputActionValue& Value)
{
}

void AEvePlayerController::Char1Skill(const FInputActionValue& Value)
{
	if (OnTriggerAction)
		SupportCharUltimateSkill(0);
	else
		SupportCharActiveSkill(0);
}

void AEvePlayerController::Char2Skill(const FInputActionValue& Value)
{
	if (OnTriggerAction)
		SupportCharUltimateSkill(1);
	else
		SupportCharActiveSkill(1);
}

void AEvePlayerController::Char3Skill(const FInputActionValue& Value)
{
	if (OnTriggerAction)
		SupportCharUltimateSkill(2);
	else
		SupportCharActiveSkill(2);
}

void AEvePlayerController::SupportCharActiveSkill(int index)
{
	if (SupportCharacters.Num() > index)
	{
		FVector Loction = CurCharacter->GetActorLocation();
		FRotator Rotation = CurCharacter->GetActorRotation();
		SupportCharacters[index]->SetActorLocationAndRotation(Loction, Rotation);
		SupportCharacters[index]->GetMesh()->SetVisibility(true);
		SupportCharacters[index]->TriggerSkill1();
	}
}

void AEvePlayerController::SupportCharUltimateSkill(int index)
{
	if (SupportCharacters.Num() > index)
	{
		FVector Loction = CurCharacter->GetActorLocation();
		FRotator Rotation = CurCharacter->GetActorRotation();
		SupportCharacters[index]->SetActorLocationAndRotation(Loction, Rotation);
		SupportCharacters[index]->GetMesh()->SetVisibility(true);
		SupportCharacters[index]->TriggerUltimateSkill();
	}
}

void AEvePlayerController::UIPlayerNormalAttack()
{
	NormalAttackStart();
}
