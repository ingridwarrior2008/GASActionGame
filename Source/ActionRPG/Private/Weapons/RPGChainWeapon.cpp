// Copyright Epic Games, Inc. All Rights Reserved.


#include "Weapons/RPGChainWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CableComponent.h"
#include "RPGCharacterBase.h"
#include "Weapons/RPGChainInterface.h"
#include "Weapons/RPGChainMovement.h"

ARPGChainWeapon::ARPGChainWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ChainRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChainRootComponent"));
	RootComponent = ChainRootComponent;
	
	ChainComponent = CreateDefaultSubobject<UCableComponent>(TEXT("ChainComponent"));
	ChainComponent->SetupAttachment(RootComponent);

	ChainMovablePointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChainMovablePointComponent"));
	ChainMovablePointComponent->SetupAttachment(RootComponent);

	BladeMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BladeMeshComponent"));
	BladeMeshComponent->SetupAttachment(ChainMovablePointComponent);

	AttackCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionComponent"));
	AttackCollisionComponent->SetupAttachment(BladeMeshComponent);
}

void ARPGChainWeapon::BeginPlay()
{
	Super::BeginPlay();

	ChainComponent->SetVisibility(false);
	AttackCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARPGChainWeapon::OnChainAttackBeginOverlap);
}

void ARPGChainWeapon::OnStartChainAttack(const ERPGChainWeaponAttack ChainWeaponAttack)
{
	if (IsValid(ChainMovementActor))
	{
		ChainMovementActor->OnChainMovementFinishedDelegate.RemoveAll(this);
		ChainMovementActor->Destroy();
		ChainMovementActor = nullptr;
	}
	
	ARPGCharacterBase* CharacterBase = Cast<ARPGCharacterBase>(GetInstigator());
	if (!IsValid(CharacterBase) || !IsValid(CharacterBase->GetMesh()) || !CharacterBase->Implements<URPGChainInterface>())
	{
		return;
	}

	const USceneComponent* ChainMovementSpawnPoint = IRPGChainInterface::Execute_BP_GetChainMovementSpawnPoint(CharacterBase);
	if (!IsValid(ChainMovementSpawnPoint))
	{
		return;
	}
	
	CurrentChainAttack = ChainWeaponAttack;
	if (AttackMap.Contains(CurrentChainAttack))
	{
		const FRPGChainWeaponConfig& WeaponConfig = AttackMap[CurrentChainAttack];
		const TSubclassOf<ARPGChainMovement>& ChainMovementClass = WeaponConfig.ChainMovementClass;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = CharacterBase;
		ChainMovementActor = GetWorld()->SpawnActor<ARPGChainMovement>(ChainMovementClass, ChainMovementSpawnPoint->GetComponentLocation(), ChainMovementSpawnPoint->GetComponentRotation(), SpawnParameters);
		if (IsValid(ChainMovementActor))
		{
			AttackCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			ChainComponent->SetVisibility(true);
			ChainMovablePointComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			ChainMovementActor->OnChainMovementFinishedDelegate.AddDynamic(this, &ARPGChainWeapon::ARPGChainWeapon::OnChainMovementFinishedCallback);

			const FVector& InitialPoint = CharacterBase->GetMesh()->GetSocketLocation(WeaponConfig.HandSocket);
			ChainMovementActor->OnStartChainMovement(ChainMovablePointComponent, BladeMeshComponent, InitialPoint, WeaponConfig.PlayRate, WeaponConfig.bCanReverseAnimation);
		}
	}
}

void ARPGChainWeapon::OnStopChainAttack()
{
	if (IsValid(ChainMovementActor))
	{
		ChainMovementActor->OnStopChainMovement();
	}
}

void ARPGChainWeapon::OnChainMovementFinishedCallback()
{
	if (IsValid(ChainMovementActor))
	{
		ChainComponent->SetVisibility(false);
		const FAttachmentTransformRules& ChainAttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);
		ChainMovablePointComponent->AttachToComponent(RootComponent, ChainAttachmentRules);
		ChainMovementActor->OnChainMovementFinishedDelegate.RemoveAll(this);
		ChainMovementActor->Destroy();
	}
}

void ARPGChainWeapon::OnChainAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || OtherActor == GetInstigator() || !AttackMap.Contains(CurrentChainAttack))
	{
		return;
	}

	ARPGCharacterBase* CharacterBase = Cast<ARPGCharacterBase>(OtherActor);
	if (IsValid(CharacterBase))
	{
		const FRPGChainWeaponConfig& WeaponConfig = AttackMap[CurrentChainAttack];

		FGameplayEventData Payload;
		Payload.Instigator = GetInstigator();
		Payload.Target = CharacterBase;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), WeaponConfig.ChainAttackTag, Payload);

		if (WeaponConfig.bCanKnockBack)
		{
			const FVector& CharacterKnockBackVector = CharacterBase->GetActorForwardVector() * WeaponConfig.KnockBackForce;
			const FVector& CharacterKnockBackForce = FVector(CharacterKnockBackVector.X, CharacterKnockBackVector.Y,  CharacterKnockBackVector.Z + WeaponConfig.KnockBackUpForce);
			CharacterBase->LaunchCharacter(CharacterKnockBackForce, true, true);
		}
	}
}
