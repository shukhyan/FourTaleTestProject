// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FourTaleAbilitySystemComponent.generated.h"

UCLASS()
class FOURTALETESTPROJECT_API UFourTaleAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void ClearAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

private:
	UPROPERTY()
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> ActiveAbilitiesHandles;
};
