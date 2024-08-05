// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FourTaleWeaponBase.generated.h"

class UWeaponDataAsset;
class UGameplayAbilitySet;
class AFourTaleProjectileBase;

UCLASS()
class FOURTALETESTPROJECT_API AFourTaleWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AFourTaleWeaponBase();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetMuzzleSocketLocation() const;

	FORCEINLINE UWeaponDataAsset* GetWeaponDataAsset() const { return WeaponDataAsset; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Components")
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|DataAsset")
	TObjectPtr<UWeaponDataAsset> WeaponDataAsset;
};
