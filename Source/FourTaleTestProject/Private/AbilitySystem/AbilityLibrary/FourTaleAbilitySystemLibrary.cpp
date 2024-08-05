// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityLibrary/FourTaleAbilitySystemLibrary.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FourTalePlayerState.h"
#include "UI/HUD/FourTaleHUD.h"
#include "UI/WidgetController/FourTaleWidgetController.h"
#include "Weapons/Common/FourTaleProjectileBase.h"

void UFourTaleAbilitySystemLibrary::SpawnProjectile(AActor* OwningActor, AActor* Weapon, const TSubclassOf<AFourTaleProjectileBase>& ProjectileClass,
                                                    const FVector& ProjectileTargetLocation, const FVector& SocketLocation, bool bOverridePitch, float PitchOverride)
{
	if (!OwningActor->HasAuthority()) return;
	
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Weapon;
	const APlayerState* PlayerState = Cast<APlayerState>(OwningActor);
	SpawnParameters.Instigator = PlayerState->GetPawn();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	UWorld* World = OwningActor->GetWorld();
	AFourTaleProjectileBase* Projectile = World->SpawnActor<AFourTaleProjectileBase>(ProjectileClass, SpawnTransform, SpawnParameters);
	Projectile->FinishSpawning(SpawnTransform);
}

UOverlayWidgetController* UFourTaleAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
    	AFourTaleHUD* FourTaleHUD = nullptr;
    	if (MakeWidgetControllerParams(WorldContextObject, WCParams, FourTaleHUD))
    	{
    		return FourTaleHUD->GetOverlayWidgetController(WCParams);
    	}
    	return nullptr;
}

bool UFourTaleAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject,
	FWidgetControllerParams& OutWCParams, AFourTaleHUD*& OutFourTaleHUD)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!IsValid(PC)) return false;
	
	OutFourTaleHUD = Cast<AFourTaleHUD>(PC->GetHUD());
	if (!IsValid(OutFourTaleHUD)) return false;
	
	AFourTalePlayerState* PS = PC->GetPlayerState<AFourTalePlayerState>();
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();

	OutWCParams.AttributeSet = AS;
	OutWCParams.AbilitySystemComponent = ASC;
	OutWCParams.PlayerState = PS;
	OutWCParams.PlayerController = PC;
	return true;
}
