// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FourTaleGameplayAbility.generated.h"

class AFourTaleCharacter;

UCLASS()
class FOURTALETESTPROJECT_API UFourTaleGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	FORCEINLINE FGameplayTag GetInputTag() const { return InputTag; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AFourTaleCharacter* GetOwningCharacter();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="FourTale|Input")
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Character")
	TObjectPtr<AFourTaleCharacter> OwningCharacter;
};
