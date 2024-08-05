// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FourTaleAbilitySystemLibrary.generated.h"

class AFourTaleHUD;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class AFourTaleProjectileBase;

UCLASS()
class FOURTALETESTPROJECT_API UFourTaleAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FourTaleAbilitySystemLibrary|Projectile")
	static void SpawnProjectile(AActor* OwningActor, AActor* Weapon, const TSubclassOf<AFourTaleProjectileBase>& ProjectileClass, const FVector& ProjectileTargetLocation, const FVector& SocketLocation, bool bOverridePitch = false, float PitchOverride = 0.f);

	UFUNCTION(BlueprintPure, Category = "FourTaleAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "FourTaleAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AFourTaleHUD*& OutFourTaleHUD);

};
