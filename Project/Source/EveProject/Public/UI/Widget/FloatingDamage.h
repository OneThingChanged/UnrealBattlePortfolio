// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingDamage.generated.h"

UCLASS()
class UFloatingDamage : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopupAnimation;

	FWidgetAnimationDynamicEvent PopupAnimationEndDelegate;

	UFUNCTION()
	void OnFinishFloating();

public:
	FSimpleDelegate OnFinishFloatingDelegate;

	void Show(float InDamage, FColor Color);

};
