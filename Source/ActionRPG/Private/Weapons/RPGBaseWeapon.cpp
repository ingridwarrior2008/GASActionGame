// Copyright Epic Games, Inc. All Rights Reserved.


#include "Weapons/RPGBaseWeapon.h"

ARPGBaseWeapon::ARPGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARPGBaseWeapon::InitializeProperties(URPGWeaponItem* InWeaponItem, const FRPGItemSlot& InItemSlot)
{
	WeaponItem = InWeaponItem;
	ItemSlot = InItemSlot;
	BP_InitializeProperties(InWeaponItem, InItemSlot);
}

URPGWeaponItem* ARPGBaseWeapon::BP_GetWeaponItem_Implementation() const
{
	return WeaponItem;
}

FRPGItemSlot ARPGBaseWeapon::GetItemSlot_Implementation() const
{
	return ItemSlot;
}
