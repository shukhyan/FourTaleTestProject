// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/FireGameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystem/AbilityLibrary/FourTaleAbilitySystemLibrary.h"
#include "Character/FourTaleCharacter.h"
#include "Weapons/Common/FourTaleWeaponBase.h"
#include "Weapons/Common/WeaponDataAsset.h"

void UFireGameplayAbility::Fire(const FVector& MuzzleLocation)
{
	if (!IsValid(GetOwningCharacter())) return;

	AFourTaleWeaponBase* Weapon = OwningCharacter->GetWeapon();
	const UWeaponDataAsset* WeaponDataAsset = Weapon->GetWeaponDataAsset();
	const TSubclassOf<AFourTaleProjectileBase> ProjectileClass = WeaponDataAsset->GetProjectileClass();
	const UCameraComponent* CameraComponent = OwningCharacter->GetCameraComponent();

	const FVector CameraLocation = CameraComponent->GetComponentLocation();
	const FRotator CurrentRotation = OwningCharacter->GetController()->GetControlRotation();
	const FVector ForwardVectorOffset = UKismetMathLibrary::GetForwardVector(CurrentRotation) * WeaponDataAsset->GetMaxDamageRange();
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwningCharacter);
	ActorsToIgnore.Add(Weapon);
	FHitResult HitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), CameraLocation, CameraLocation + ForwardVectorOffset, TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
	const FVector HitLocation = HitResult.bBlockingHit ? HitResult.Location : HitResult.TraceEnd;
	
	UFourTaleAbilitySystemLibrary::SpawnProjectile(GetOwningActorFromActorInfo(), Weapon, ProjectileClass, HitLocation, MuzzleLocation);
}

AFourTaleWeaponBase* UFireGameplayAbility::GetCurrentWeapon()
{
	return GetOwningCharacter()->GetWeapon();
}
