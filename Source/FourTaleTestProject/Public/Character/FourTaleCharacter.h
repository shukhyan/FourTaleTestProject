// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FourTaleCharacter.generated.h"

class UCharacterDataAsset;
class AFourTaleWeaponBase;
class USpringArmComponent;
class UCameraComponent;
class UAttributeSet;

UCLASS()
class FOURTALETESTPROJECT_API AFourTaleCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AFourTaleCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION()
	virtual void OnRep_Weapon();
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_HandleDeath();
	
	virtual void Die();

	bool IsDead() const { return bDead; }

	/* Getters */
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE AFourTaleWeaponBase* GetWeapon() const { return Weapon; }
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void EquipWeapon();
	
	UFUNCTION(BlueprintCallable)
	virtual void UnEquipWeapon();
	
	UFUNCTION(BlueprintCallable)
	int ChangeCurrentWeaponIndex(const bool ToNext);
	
	virtual void SpawnWeapon(const TSubclassOf<AFourTaleWeaponBase>& SpawningWeaponClass);
	virtual void InitWeapon(const AFourTaleWeaponBase* WeaponToInit) const;

	virtual void InitActorInfo();
	virtual void InitAbilities();
	virtual void InitHUD();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Assets")
	TObjectPtr<UCharacterDataAsset> CharacterDataAsset;
	
	UPROPERTY(BlueprintReadOnly)
	bool bDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FourTale|Sounds")
	USoundBase* DeathSound;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FourTale|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FourTale|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FourTale|ASC", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(ReplicatedUsing = OnRep_Weapon, EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AFourTaleWeaponBase> Weapon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FourTale|Weapon", meta = (AllowPrivateAccess = "true"))
	FName WeaponSocket;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY()
	int CurrentWeaponIndex = 0;
};
