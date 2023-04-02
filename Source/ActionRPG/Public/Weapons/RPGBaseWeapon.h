// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGBaseWeapon.generated.h"

class URPGWeaponItem;
UCLASS()
class ACTIONRPG_API ARPGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ARPGBaseWeapon();

	
	UFUNCTION(BlueprintCallable)
	void InitializeProperties(URPGWeaponItem* WeaponItem, const FRPGItemSlot& ItemSlot);

protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_InitializeProperties(URPGWeaponItem* WeaponItem, const FRPGItemSlot& ItemSlot);


	virtual void BeginPlay() override;
	
};
