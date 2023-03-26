// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/RPGGameplayAbility.h"
#include "RPGSmashFuryAbility.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API URPGSmashFuryAbility : public URPGGameplayAbility
{
	GENERATED_BODY()


protected:

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;


	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* SkillAnimMontage;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer SkillsAnimMontageTag;

private:
	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnInterrupted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData);
	
	UFUNCTION()
	void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData);
};

