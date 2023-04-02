// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGDoubleWeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGDoubleWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONRPG_API IRPGDoubleWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void BP_AttachDoubleWeaponToComponent(USceneComponent* Parent, const EAttachmentRule LocationRule, const EAttachmentRule RotationRule, const EAttachmentRule ScaleRule, const bool bWeldSimulatedBodies);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void BP_DetachDoubleWeaponFromActor(const EDetachmentRule LocationRule = EDetachmentRule::KeepRelative, const EDetachmentRule RotationRule = EDetachmentRule::KeepRelative, const EDetachmentRule ScaleRule = EDetachmentRule::KeepRelative);
};
