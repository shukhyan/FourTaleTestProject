// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/FourTaleWidgetController.h"
#include "AbilitySystem/FourTaleAbilitySystemComponent.h"
#include "AbilitySystem/FourTaleAttributeSet.h"
#include "Player/FourTalePlayerController.h"
#include "Player/FourTalePlayerState.h"

void UFourTaleWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UFourTaleWidgetController::BroadcastInitialValues()
{
}

void UFourTaleWidgetController::BindCallbacksToDependencies()
{
}

AFourTalePlayerController* UFourTaleWidgetController::GetFourTalePC()
{
	if (!IsValid(FourTalePlayerController))
	{
		FourTalePlayerController = Cast<AFourTalePlayerController>(PlayerController);
	}
	return FourTalePlayerController;
}

AFourTalePlayerState* UFourTaleWidgetController::GetFourTalePS()
{
	if (!IsValid(FourTalePlayerState))
	{
		FourTalePlayerState = Cast<AFourTalePlayerState>(PlayerState);
	}
	return FourTalePlayerState;
}

UFourTaleAbilitySystemComponent* UFourTaleWidgetController::GetFourTaleASC()
{
	if (!IsValid(FourTaleAbilitySystemComponent))
	{
		FourTaleAbilitySystemComponent = Cast<UFourTaleAbilitySystemComponent>(AbilitySystemComponent);
	}
	return FourTaleAbilitySystemComponent;
}

UFourTaleAttributeSet* UFourTaleWidgetController::GetFourTaleAS()
{
	if (!IsValid(FourTaleAttributeSet))
	{
		FourTaleAttributeSet = Cast<UFourTaleAttributeSet>(AttributeSet);
	}
	return FourTaleAttributeSet;
}