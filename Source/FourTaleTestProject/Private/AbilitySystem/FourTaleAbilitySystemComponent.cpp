// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/FourTaleAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/FourTaleGameplayAbility.h"

void UFourTaleAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
			
		AbilitySpecInputPressed(AbilitySpec);
		if (AbilitySpec.IsActive())
		{
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}

void UFourTaleAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
		
		AbilitySpecInputPressed(AbilitySpec);
		if (!AbilitySpec.IsActive())
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UFourTaleAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) || !AbilitySpec.IsActive()) continue;
		
		AbilitySpecInputReleased(AbilitySpec);
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
	}
}

void UFourTaleAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : AbilityClasses)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UFourTaleGameplayAbility* FourTaleAbility = Cast<UFourTaleGameplayAbility>(AbilitySpec.Ability))
		{
			FGameplayTag InputTag = FourTaleAbility->GetInputTag();
			AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
			FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(AbilitySpec);
			ActiveAbilitiesHandles.Add(InputTag, AbilitySpecHandle);
		}
	}
}

void UFourTaleAbilitySystemComponent::ClearAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : AbilityClasses)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UFourTaleGameplayAbility* FourTaleAbility = Cast<UFourTaleGameplayAbility>(AbilitySpec.Ability))
		{
			FGameplayTag InputTag = FourTaleAbility->GetInputTag();
			AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
			const FGameplayAbilitySpecHandle* SpecHandle = ActiveAbilitiesHandles.Find(InputTag);
			ClearAbility(*SpecHandle);
		}
	}
}
