// Fill out your copyright notice in the Description page of Project Settings.


#include "AI\Blackboard\BTService_ChangeSpeed.h"

#include "AIController.h"
#include "Character/EveCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (auto Controller = OwnerComp.GetAIOwner())
	{
		if (auto* Enemy = Cast<AEveCharacter>(Controller->GetPawn()))
		{
			Enemy->GetCharacterMovement()->MaxWalkSpeed = Speed;
		}
	}
}