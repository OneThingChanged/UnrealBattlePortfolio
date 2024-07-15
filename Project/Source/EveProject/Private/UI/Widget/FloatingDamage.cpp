// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/FloatingDamage.h"
#include "Components/TextBlock.h"

void UFloatingDamage::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PopupAnimationEndDelegate.BindDynamic(this, &ThisClass::OnFinishFloating);
	BindToAnimationFinished(PopupAnimation, PopupAnimationEndDelegate);

}

void UFloatingDamage::Show(float InDamage, FColor Color)
{
	DamageText->SetText(FText::AsNumber(InDamage));

	FSlateColor SlateColor(Color);
	DamageText->SetColorAndOpacity(SlateColor);

	PlayAnimation(PopupAnimation);
}

void UFloatingDamage::OnFinishFloating()
{
	OnFinishFloatingDelegate.Execute();
}