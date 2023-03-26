// Copyright Epic Games, Inc. All Rights Reserved.


#include "Abilities/RPGEffectActor.h"

// Sets default values
ARPGEffectActor::ARPGEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARPGEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

