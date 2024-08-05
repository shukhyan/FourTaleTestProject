// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Input/FourTaleInputConfig.h"
#include "InputAction.h"

const UInputAction* UFourTaleInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const auto& [ActionInputAction, ActionInputTag]: AbilityInputActions)
	{
		if (IsValid(ActionInputAction) && ActionInputTag == InputTag)
		{
			return ActionInputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
