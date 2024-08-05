// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FourTaleCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/FourTaleAbilitySystemComponent.h"
#include "Character/CharacterDataAsset.h"
#include "Player/FourTalePlayerController.h"
#include "Player/FourTalePlayerState.h"
#include "UI/HUD/FourTaleHUD.h"
#include "Weapons/Common/FourTaleWeaponBase.h"
#include "Weapons/Common/WeaponDataAsset.h"

AFourTaleCharacter::AFourTaleCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = true;
}

void AFourTaleCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFourTaleCharacter, Weapon);
}

void AFourTaleCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitActorInfo();
}

void AFourTaleCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability actor info for the Client
	InitActorInfo();
}

void AFourTaleCharacter::OnRep_Weapon()
{
	InitWeapon(Weapon);
	const TObjectPtr<UAnimMontage> EquipMontage = Weapon->GetWeaponDataAsset()->GetEquipMontage();
	PlayAnimMontage(EquipMontage);
}

void AFourTaleCharacter::SpawnWeapon(const TSubclassOf<AFourTaleWeaponBase>& SpawningWeaponClass)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetMesh()->GetSocketLocation(WeaponSocket));
	SpawnTransform.SetRotation(GetMesh()->GetSocketRotation(WeaponSocket).Quaternion());
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Weapon = GetWorld()->SpawnActor<AFourTaleWeaponBase>(SpawningWeaponClass, SpawnTransform, SpawnParameters);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
}

void AFourTaleCharacter::InitWeapon(const AFourTaleWeaponBase* WeaponToInit) const
{
	const UWeaponDataAsset* WeaponDataAsset = WeaponToInit->GetWeaponDataAsset();
	if (!IsValid(WeaponDataAsset)) return;
	
	const TSubclassOf<UAnimInstance> WeaponAnimLayer = WeaponDataAsset->GetWeaponAnimLayer();
	if (!IsValid(WeaponAnimLayer)) return;
	
	GetMesh()->SetAnimClass(WeaponAnimLayer);
}

void AFourTaleCharacter::Die()
{
	if (UFourTaleAbilitySystemComponent* FourTaleASC = Cast<UFourTaleAbilitySystemComponent>(AbilitySystemComponent); IsValid(FourTaleASC))
	{
		FourTaleASC->ClearAbilities(CharacterDataAsset->GetCharacterAbilities());
	}
	
	Multicast_HandleDeath();
}

void AFourTaleCharacter::Multicast_HandleDeath_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bDead = true;

	if (IsValid(DeathSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
}

void AFourTaleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	EquipWeapon();
}

void AFourTaleCharacter::EquipWeapon()
{
	if (!HasAuthority()) return;
	
	const TArray<TSubclassOf<AFourTaleWeaponBase>>& WeaponClasses = CharacterDataAsset->GetWeapons();
	if (WeaponClasses.IsEmpty()) return;
	
	const TSubclassOf<AFourTaleWeaponBase> CurrentWeapon = WeaponClasses[CurrentWeaponIndex];
	if (!IsValid(CurrentWeapon)) return;
	
	SpawnWeapon(CurrentWeapon);
	InitWeapon(Weapon);
}

void AFourTaleCharacter::UnEquipWeapon()
{
	Weapon->Destroy();
}

int AFourTaleCharacter::ChangeCurrentWeaponIndex(const bool ToNext)
{
	const int LastIndex = CharacterDataAsset->GetWeapons().Num() - 1;
	if (ToNext)
	{
		++CurrentWeaponIndex;
		if (CurrentWeaponIndex > LastIndex)
		{
			CurrentWeaponIndex = 0;
		}
	}
	else
	{
		--CurrentWeaponIndex;
		if (CurrentWeaponIndex < 0)
		{
			CurrentWeaponIndex = LastIndex;
		}
	}

	return CurrentWeaponIndex;
}

void AFourTaleCharacter::InitActorInfo()
{
	AFourTalePlayerState* FourTalePlayerState = GetPlayerState<AFourTalePlayerState>();
	check(FourTalePlayerState);
	FourTalePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(FourTalePlayerState, this);
	AbilitySystemComponent = Cast<UFourTaleAbilitySystemComponent>(FourTalePlayerState->GetAbilitySystemComponent());
	AttributeSet = FourTalePlayerState->GetAttributeSet();

	if (HasAuthority())
	{
		InitAbilities();
	}
	else
	{
		InitHUD();
	}
}

void AFourTaleCharacter::InitAbilities()
{
	UFourTaleAbilitySystemComponent* FourTaleASC = CastChecked<UFourTaleAbilitySystemComponent>(AbilitySystemComponent);

	if (!IsValid(CharacterDataAsset)) return;
		
	FourTaleASC->AddAbilities(CharacterDataAsset->GetCharacterAbilities());
}

void AFourTaleCharacter::InitHUD()
{
	AFourTalePlayerController* FourTalePlayerController = Cast<AFourTalePlayerController>(GetController());
	if (!IsValid(FourTalePlayerController)) return;
		
	AFourTaleHUD* FourTaleHUD  = Cast<AFourTaleHUD>(FourTalePlayerController->GetHUD());
	if (!IsValid(FourTaleHUD)) return;
		
	FourTaleHUD->InitOverlay(FourTalePlayerController, GetPlayerState(), AbilitySystemComponent, AttributeSet);

}
