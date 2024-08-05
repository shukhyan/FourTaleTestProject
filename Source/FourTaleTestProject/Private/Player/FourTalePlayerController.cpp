// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/FourTalePlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/FourTaleAbilitySystemComponent.h"
#include "AbilitySystem/Input/FourTaleInputComponent.h"

AFourTalePlayerController::AFourTalePlayerController()
{
	bReplicates = true;
}

void AFourTalePlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(MappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void AFourTalePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UFourTaleInputComponent* FourTaleInputComponent = CastChecked<UFourTaleInputComponent>(InputComponent);
	
	FourTaleInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFourTalePlayerController::Move);
	FourTaleInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFourTalePlayerController::Look);
	FourTaleInputComponent->BindAbilityActions(InputConfig, this, &AFourTalePlayerController::AbilityInputTagPressed, &AFourTalePlayerController::AbilityInputTagReleased, &AFourTalePlayerController::AbilityInputTagHeld);
}

void AFourTalePlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (!IsValid(GetControlledPawn())) return;
	
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
}

void AFourTalePlayerController::Look(const FInputActionValue& InputActionValue)
{
	if (!IsValid(GetControlledPawn())) return;
	
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	ControlledPawn->AddControllerYawInput(LookAxisVector.X);
	ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
}

void AFourTalePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void AFourTalePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
}

void AFourTalePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
}

UFourTaleAbilitySystemComponent* AFourTalePlayerController::GetASC()
{
	if (!IsValid(FourTaleAbilitySystemComponent))
	{
		FourTaleAbilitySystemComponent = Cast<UFourTaleAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return FourTaleAbilitySystemComponent;
}

TObjectPtr<APawn> AFourTalePlayerController::GetControlledPawn()
{
	if (!IsValid(ControlledPawn))
	{
		ControlledPawn = GetPawn<APawn>();
	}
	return ControlledPawn;
}
