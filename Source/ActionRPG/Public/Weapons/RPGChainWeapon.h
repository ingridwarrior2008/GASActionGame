// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Weapons/RPGBaseWeapon.h"
#include "RPGChainWeapon.generated.h"

class UCableComponent;
class USkeletalMeshComponent;
class ARPGChainMovement;

UENUM(BlueprintType)
enum class ERPGChainWeaponAttack : uint8
{
	Attack_DefaultLeft,
	Attack_DefaultRight,
	Attack_Whirlwind,
	Attack_UltraWhirlwind,
	Attack_Grapple
};

/**
 * Structs that contains the chain weapon configuration.
 */
USTRUCT(BlueprintType)
struct FRPGChainWeaponConfig
{
	
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARPGChainMovement> ChainMovementClass;

	UPROPERTY(EditDefaultsOnly)
	float PlayRate;

	UPROPERTY(EditDefaultsOnly)
	uint8 bCanReverseAnimation : 1;

	UPROPERTY(EditDefaultsOnly)
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly)
	uint8 bCanKnockBack : 1;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bCanKnockBack", EditConditionHides))
	float KnockBackForce;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bCanKnockBack", EditConditionHides))
	float KnockBackUpForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag  ChainAttackTag;
	
	FRPGChainWeaponConfig()
	{
		bCanReverseAnimation = true;
		bCanKnockBack = true;
		PlayRate = 1.0f;
		HandSocket = TEXT("ChainThrow_L");
		KnockBackForce = -1500.0f;
		KnockBackUpForce = 100;
	}
};

/**
 * Base class for that handle Chain weapon.
 */
UCLASS()
class ACTIONRPG_API ARPGChainWeapon : public ARPGBaseWeapon
{
	GENERATED_BODY()

public:
	ARPGChainWeapon();

	UFUNCTION(BlueprintCallable)
	void OnStartChainAttack(const ERPGChainWeaponAttack ChainWeaponAttack);

	UFUNCTION(BlueprintCallable)
	void OnStopChainAttack();

protected:

	UPROPERTY(EditDefaultsOnly)
	TMap<ERPGChainWeaponAttack, FRPGChainWeaponConfig> AttackMap;

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnChainMovementFinishedCallback();

	UFUNCTION()
	void OnChainAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	void EnableChainAttack(const bool bEnable);

	UPROPERTY(Transient)
	ERPGChainWeaponAttack CurrentChainAttack;

	UPROPERTY(Transient)
	ARPGChainMovement* ChainMovementActor;

	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BladeMeshComponent;

	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ChainMovablePointComponent;
	
	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCableComponent* ChainComponent;

	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ChainRootComponent;

	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* AttackCollisionComponent;
};
