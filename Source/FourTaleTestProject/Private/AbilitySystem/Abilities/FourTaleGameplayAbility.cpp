// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/FourTaleGameplayAbility.h"
#include "Character/FourTaleCharacter.h"

AFourTaleCharacter* UFourTaleGameplayAbility::GetOwningCharacter()
{
	if (!IsValid(OwningCharacter))
	{
		OwningCharacter = Cast<AFourTaleCharacter>(GetAvatarActorFromActorInfo());
	}
	return OwningCharacter;
}
