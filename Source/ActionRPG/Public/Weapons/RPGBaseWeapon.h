// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGBaseWeapon.generated.h"

class URPGWeaponItem;

/**
 * Base class for handle the game weapons.
 */
UCLASS()
class ACTIONRPG_API ARPGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ARPGBaseWeapon();
	
	UFUNCTION(BlueprintCallable)
	void InitializeProperties(URPGWeaponItem* InWeaponItem, const FRPGItemSlot& InItemSlot);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	URPGWeaponItem* BP_GetWeaponItem() const;
	virtual URPGWeaponItem* BP_GetWeaponItem_Implementation() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	FRPGItemSlot GetItemSlot() const;
	virtual FRPGItemSlot GetItemSlot_Implementation() const;
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_InitializeProperties(URPGWeaponItem* InWeaponItem, const FRPGItemSlot& InItemSlot);
	
	UPROPERTY(Transient)
	URPGWeaponItem* WeaponItem;

	UPROPERTY(Transient)
	FRPGItemSlot ItemSlot;
};
