// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "FourTaleInputConfig.h"
#include "FourTaleInputComponent.generated.h"

UCLASS()
class FOURTALETESTPROJECT_API UFourTaleInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UFourTaleInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UFourTaleInputComponent::BindAbilityActions(const UFourTaleInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	
	for (const auto& [ActionInputAction, ActionInputTag] : InputConfig->GetAbilityInputActions())
	{
		if (!IsValid(ActionInputAction) || !ActionInputTag.IsValid()) continue;
		
		if (PressedFunc)
		{
			BindAction(ActionInputAction, ETriggerEvent::Started, Object, PressedFunc, ActionInputTag);
		}

		if (ReleasedFunc)
		{
			BindAction(ActionInputAction, ETriggerEvent::Completed, Object, ReleasedFunc, ActionInputTag);
		}
		
		if (HeldFunc)
		{
			BindAction(ActionInputAction, ETriggerEvent::Triggered, Object, HeldFunc, ActionInputTag);
		}
	}
}
