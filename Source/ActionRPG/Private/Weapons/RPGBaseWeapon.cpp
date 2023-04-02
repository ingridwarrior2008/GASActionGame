// Copyright Epic Games, Inc. All Rights Reserved.


#include "Weapons/RPGBaseWeapon.h"

ARPGBaseWeapon::ARPGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARPGBaseWeapon::InitializeProperties(URPGWeaponItem* WeaponItem, const FRPGItemSlot& ItemSlot)
{
	BP_InitializeProperties(WeaponItem, ItemSlot);
}

void ARPGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
