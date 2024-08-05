// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

class AFourTaleProjectileBase;

UCLASS()
class FOURTALETESTPROJECT_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE TSubclassOf<AFourTaleProjectileBase> GetProjectileClass() const { return ProjectileClass; }
	FORCEINLINE TSubclassOf<UAnimInstance> GetWeaponAnimLayer() const { return WeaponAnimLayer; }
	FORCEINLINE TObjectPtr<UAnimMontage> GetEquipMontage() const { return EquipMontage; }
	FORCEINLINE float GetMaxDamageRange() const { return MaxDamageRange; }
	FORCEINLINE FName GetMuzzleSocket() const { return MuzzleSocket; }
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFourTaleProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UAnimInstance> WeaponAnimLayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	float MaxDamageRange = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	FName MuzzleSocket = "Muzzle";
};
