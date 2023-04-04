// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGChainMovement.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRPGOnChainMovementFinishedSignature);

/**
 * Base class for Chain movement for the moment its using spline movement.
 */
UCLASS()
class ACTIONRPG_API ARPGChainMovement : public AActor
{
	GENERATED_BODY()
	
public:	
	ARPGChainMovement();

	
	virtual void OnStartChainMovement(USceneComponent* ChainMovablePoint, USkeletalMeshComponent* WeaponMesh, const FVector& InitialPoint,  float PlayRate = 1.0f, const bool bCanReverseAnimation = true);

	virtual void OnStopChainMovement();
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FRPGOnChainMovementFinishedSignature OnChainMovementFinishedDelegate;
	
protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_OnStartChainMovement(USceneComponent* ChainMovablePoint, USkeletalMeshComponent* WeaponMesh, const FVector& InitialPoint,  const float PlayRate, const bool bCanReverseAnimation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_OnStopChainMovement();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BP_OnReverseChainMovement();
	virtual void BP_OnReverseChainMovement_Implementation() { }
};
