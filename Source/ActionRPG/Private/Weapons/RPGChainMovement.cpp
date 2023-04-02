// Copyright Epic Games, Inc. All Rights Reserved.


#include "Weapons/RPGChainMovement.h"

ARPGChainMovement::ARPGChainMovement()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARPGChainMovement::OnStartChainMovement(USceneComponent* ChainMovablePoint, USkeletalMeshComponent* WeaponMesh, const FVector& InitialPoint, const float PlayRate, const bool bCanReverseAnimation)
{
	BP_OnStartChainMovement(ChainMovablePoint, WeaponMesh, InitialPoint, PlayRate, bCanReverseAnimation);
}

void ARPGChainMovement::OnStopChainMovement()
{
	BP_OnStopChainMovement();
}