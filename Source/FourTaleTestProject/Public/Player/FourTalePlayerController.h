// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FourTalePlayerController.generated.h"

struct FGameplayTag;
class UFourTaleAbilitySystemComponent;
class UFourTaleInputConfig;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class FOURTALETESTPROJECT_API AFourTalePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFourTalePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UFourTaleAbilitySystemComponent* GetASC();
	TObjectPtr<APawn> GetControlledPawn();
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UFourTaleInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UFourTaleAbilitySystemComponent> FourTaleAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<APawn> ControlledPawn;

};
