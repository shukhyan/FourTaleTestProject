// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FourTaleGameplayAbility.h"
#include "FireGameplayAbility.generated.h"

class AFourTaleWeaponBase;

UCLASS()
class FOURTALETESTPROJECT_API UFireGameplayAbility : public UFourTaleGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	virtual void Fire(const FVector& MuzzleLocation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AFourTaleWeaponBase* GetCurrentWeapon();
};
