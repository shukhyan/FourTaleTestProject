// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FourTalePlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/FourTaleAbilitySystemComponent.h"
#include "AbilitySystem/FourTaleAttributeSet.h"

AFourTalePlayerState::AFourTalePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UFourTaleAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UFourTaleAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}
