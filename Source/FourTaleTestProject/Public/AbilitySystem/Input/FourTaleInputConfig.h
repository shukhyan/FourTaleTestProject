// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FourTaleInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FFourTaleInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class FOURTALETESTPROJECT_API UFourTaleInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	FORCEINLINE TArray<FFourTaleInputAction> GetAbilityInputActions() const { return AbilityInputActions; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FFourTaleInputAction> AbilityInputActions;
};
