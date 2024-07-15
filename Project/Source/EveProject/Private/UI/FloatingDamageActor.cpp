// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FloatingDamageActor.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/FloatingDamage.h"

AFloatingDamageActor::AFloatingDamageActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootScene");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawAtDesiredSize(true);
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ProjectEve/UI/Battle/BP_DamageIndicator.BP_DamageIndicator_C'"));
	if (WidgetFinder.Succeeded() && WidgetFinder.Class != nullptr)
	{
		WidgetComponent->SetWidgetClass(WidgetFinder.Class);
	}

}

void AFloatingDamageActor::Init(float InDamage, FColor InColor)
{
	Damage = InDamage;
	Color = InColor;

	UFloatingDamage* FloatingDamage = Cast<UFloatingDamage>(WidgetComponent->GetUserWidgetObject());
	if (FloatingDamage)
	{
		FloatingDamage->OnFinishFloatingDelegate.BindWeakLambda(this, [&]()
		{
			Destroy();
		});

		FloatingDamage->Show(Damage, Color);
	}
}

