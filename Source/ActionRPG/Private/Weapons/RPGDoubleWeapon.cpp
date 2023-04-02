// Copyright Epic Games, Inc. All Rights Reserved.


#include "Weapons/RPGDoubleWeapon.h"

void ARPGDoubleWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (!ensureMsgf(WeaponClass, TEXT("WeaponClass is null")))
	{
		return;
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = GetInstigator();
	
	LeftWeapon = GetWorld()->SpawnActor<ARPGBaseWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	RightWeapon = GetWorld()->SpawnActor<ARPGBaseWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
}

void ARPGDoubleWeapon::Destroyed()
{
	Super::Destroyed();

	if (IsValid(LeftWeapon))
	{
		LeftWeapon->Destroy();	
	}

	if (IsValid(RightWeapon))
	{
		RightWeapon->Destroy();
	}
}


void ARPGDoubleWeapon::BP_AttachDoubleWeaponToComponent_Implementation(USceneComponent* Parent, const EAttachmentRule LocationRule, const EAttachmentRule RotationRule, const EAttachmentRule ScaleRule, const bool bWeldSimulatedBodies)
{
	if (IsValid(LeftWeapon))
	{
		LeftWeapon->AttachToComponent(Parent, FAttachmentTransformRules(LocationRule, RotationRule, ScaleRule, bWeldSimulatedBodies), LeftHandSocket);	
	}

	if (IsValid(RightWeapon))
	{
		RightWeapon->AttachToComponent(Parent, FAttachmentTransformRules(LocationRule, RotationRule, ScaleRule, bWeldSimulatedBodies), RightHandSocket);	
	}
}

void ARPGDoubleWeapon::BP_DetachDoubleWeaponFromActor_Implementation(const EDetachmentRule LocationRule, const EDetachmentRule RotationRule, const EDetachmentRule ScaleRule)
{
	if (IsValid(LeftWeapon))
	{
		LeftWeapon->DetachFromActor(FDetachmentTransformRules(LocationRule, RotationRule, ScaleRule, true));
	}

	if (IsValid(RightWeapon))
	{
		RightWeapon->DetachFromActor(FDetachmentTransformRules(LocationRule, RotationRule, ScaleRule, true));	
	}
}