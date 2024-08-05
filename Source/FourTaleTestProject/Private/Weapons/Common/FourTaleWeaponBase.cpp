// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/Common/FourTaleWeaponBase.h"
#include "Weapons/Common/WeaponDataAsset.h"

AFourTaleWeaponBase::AFourTaleWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(WeaponSkeletalMeshComponent);
}

FVector AFourTaleWeaponBase::GetMuzzleSocketLocation() const
{
	return WeaponSkeletalMeshComponent->GetSocketLocation(WeaponDataAsset->GetMuzzleSocket());
}