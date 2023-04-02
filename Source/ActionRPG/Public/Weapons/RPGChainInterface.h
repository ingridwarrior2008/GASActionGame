// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGChainInterface.generated.h"

UINTERFACE(MinimalAPI)
class URPGChainInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONRPG_API IRPGChainInterface
{
	GENERATED_BODY()

public:
	/** */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Chain")
	USceneComponent* BP_GetChainMovementSpawnPoint() const;
};
