// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/Common/FourTaleProjectileBase.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"

AFourTaleProjectileBase::AFourTaleProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovement->ProjectileGravityScale = 0.f;

	LoopingSoundComponent = CreateDefaultSubobject<UAudioComponent>("LoopingSoundComponent");
	LoopingSoundComponent->SetupAttachment(GetRootComponent());
}

void AFourTaleProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	SetReplicateMovement(true);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AFourTaleProjectileBase::OnBeginOverlap);
	MeshComponent->IgnoreActorWhenMoving(GetOwner(), true);
	MeshComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void AFourTaleProjectileBase::OnHit()
{
	PlayImpactSound();
	SpawnImpactEffect();
	
	bHit = true;
}

void AFourTaleProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (MeshComponent->MoveIgnoreActors.Contains(OtherActor)) return;
	
	if (!bHit) OnHit();
	
	if (HasAuthority())
	{
		CauseDamage(OtherActor);
		Destroy();
	}
	else bHit = true;
}

void AFourTaleProjectileBase::CauseDamage(AActor* TargetActor)
{
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetInstigator());
	if (!IsValid(OwnerASC)) return;

	const FGameplayEffectContextHandle EffectContextHandle = OwnerASC->MakeEffectContext();
	const FGameplayEffectSpecHandle DamageSpecHandle = OwnerASC->MakeOutgoingSpec(DamageEffectClass, 1.f, EffectContextHandle);
	OwnerASC->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

void AFourTaleProjectileBase::PlayImpactSound() const
{
	if (!IsValid(ImpactSound)) return;
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
}

void AFourTaleProjectileBase::SpawnImpactEffect() const
{
	if (!IsValid(ImpactEffect)) return;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
}
