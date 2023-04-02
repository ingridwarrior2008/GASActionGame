// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RPGDoubleWeaponInterface.h"
#include "Weapons/RPGBaseWeapon.h"
#include "RPGDoubleWeapon.generated.h"

UENUM(BlueprintType)
enum class ERPGWeaponType : uint8
{
	Left,
	Right
};

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARPGDoubleWeapon : public ARPGBaseWeapon, public IRPGDoubleWeaponInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	ARPGBaseWeapon* GetWeapon(const ERPGWeaponType WeaponType) const { return WeaponType == ERPGWeaponType::Left ? LeftWeapon : RightWeapon;  }

#pragma region IRPGDoubleWeaponInterface
	virtual void BP_AttachDoubleWeaponToComponent_Implementation(USceneComponent* Parent, const EAttachmentRule LocationRule, const EAttachmentRule RotationRule, const EAttachmentRule ScaleRule, const bool bWeldSimulatedBodies) override;
	virtual void BP_DetachDoubleWeaponFromActor_Implementation(const EDetachmentRule LocationRule, const EDetachmentRule RotationRule, const EDetachmentRule ScaleRule) override;
#pragma endregion IRPGDoubleWeaponInterface
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARPGBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly)
	FName LeftHandSocket;

	UPROPERTY(EditDefaultsOnly)
	FName RightHandSocket;
	
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
private:

	UPROPERTY(Transient)
	ARPGBaseWeapon* LeftWeapon;

	UPROPERTY(Transient)
	ARPGBaseWeapon* RightWeapon;
};
