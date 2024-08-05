// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"

class AFourTaleWeaponBase;
class UGameplayAbility;

UCLASS()
class FOURTALETESTPROJECT_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE TArray<TSubclassOf<UGameplayAbility>> GetCharacterAbilities() const { return CharacterAbilities; }
	FORCEINLINE TArray<TSubclassOf<AFourTaleWeaponBase>> GetWeapons() const { return Weapons; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Abilities", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> CharacterAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AFourTaleWeaponBase>> Weapons;
};
