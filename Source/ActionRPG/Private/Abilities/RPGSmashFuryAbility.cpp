// Copyright Epic Games, Inc. All Rights Reserved.


#include "Abilities/RPGSmashFuryAbility.h"

#include "Abilities/RPGAbilityTask_PlayMontageAndWaitForEvent.h"

bool URPGSmashFuryAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                              const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void URPGSmashFuryAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	URPGAbilityTask_PlayMontageAndWaitForEvent* PlayStartMontageAndWaitForEventTask = URPGAbilityTask_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, TEXT("Fury"), SkillAnimMontage, SkillsAnimMontageTag);
	if (IsValid(PlayStartMontageAndWaitForEventTask))
	{
		PlayStartMontageAndWaitForEventTask->OnCompleted.AddDynamic(this, &URPGSmashFuryAbility::OnCompleted);
		PlayStartMontageAndWaitForEventTask->OnCancelled.AddDynamic(this, &URPGSmashFuryAbility::OnCancelled);
		PlayStartMontageAndWaitForEventTask->OnInterrupted.AddDynamic(this, &URPGSmashFuryAbility::OnInterrupted);
		PlayStartMontageAndWaitForEventTask->OnBlendOut.AddDynamic(this, &URPGSmashFuryAbility::OnBlendOut);
		PlayStartMontageAndWaitForEventTask->EventReceived.AddDynamic(this, &URPGSmashFuryAbility::EventReceived);
		PlayStartMontageAndWaitForEventTask->ReadyForActivation();
	}

}

void URPGSmashFuryAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void URPGSmashFuryAbility::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
}

void URPGSmashFuryAbility::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void URPGSmashFuryAbility::OnInterrupted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void URPGSmashFuryAbility::OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void URPGSmashFuryAbility::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	ApplyEffectContainer(EventTag, EventData, -1);
}
