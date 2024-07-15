// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EveAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EveCombatCharacter.h"
#include "Component/AIComponent.h"
#include "Component/CombatComponent.h"
#include "Eve/DefineConst.h"
#include "EveProject/EveProject.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEveAIController::AEveAIController()
{
	SetupPerceptionSystem();
}

void AEveAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Z_SCREEN_LOG(1, FColor::Emerald, TEXT("%s ㅇㅇ "), *InPawn->GetName());
	if (AEveCombatCharacter* enemy = Cast<AEveCombatCharacter>(InPawn))
	{
		if (UBehaviorTree* const tree = enemy->GetAIComponent()->GetBehaviorTree())
		{
			// SetUpPerceptionParameter();
			UBlackboardComponent* blackBoard;
			UseBlackboard(tree->BlackboardAsset, blackBoard);
			Blackboard = blackBoard;
			RunBehaviorTree(tree);
			GetBlackboardComponent()->SetValueAsBool(EveConst::BlackboardKey_CanSeeTarget, false);
		}
	}
}

void AEveAIController::SetupPerceptionSystem()
{
	// SightConfig = GetComponentByClass<UAISenseConfig_Sight>();
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

		SightConfig->SightRadius = SightRadius;
		SightConfig->LoseSightRadius = LoseSightRadius;
		SightConfig->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = AutoSuccessRangeFromLastSeenLocation;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEveAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AEveAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (AEveCombatCharacter* const PlayerPawn = Cast<AEveCombatCharacter>(Actor))
	{
		if (PlayerPawn->GetSideType() != EEveSideType::Player)
			return;
		
		Z_SCREEN_LOG(1, FColor::Black, TEXT("Find Target (%s)"), *GetPawn()->GetName());

		//타겟팅 불가
		if (!PlayerPawn->IsAbleToTarget())
			return;
		
		//적 발견
		bool CanSeeTarget = Stimulus.WasSuccessfullySensed();
		GetBlackboardComponent()->SetValueAsBool(EveConst::BlackboardKey_CanSeeTarget, CanSeeTarget);
		
		auto NPC = Cast<AEveCombatCharacter>(GetPawn());
		if (CanSeeTarget)
		{
			NPC->GetCombatComponent()->SetTarget(PlayerPawn);
			GetBlackboardComponent()->SetValueAsObject(EveConst::BlackboardKey_Target, PlayerPawn);			
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject(EveConst::BlackboardKey_Target, nullptr);			
		}
		// else
		// {
		// 	// UE_LOG(LogTemp, Log, TEXT("Cannot See Target %s %s"), *GetPawn()->GetName(), *character->GetName());
		// 	NPC->GetCombatComponent()->RemoveTarget();
		// 	GetBlackboardComponent()->SetValueAsEnum(EveConst::BlackboardKey_AIStateType, static_cast<int>(EJinAIState::Patrol));
		// 	GetBlackboardComponent()->SetValueAsObject(EveConst::BlackboardKey_Target, nullptr);
		// 	
		// }
	}
}
