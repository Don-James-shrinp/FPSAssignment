// Origin OvO CopyRight Reserved


#include "AbilitySystem/Abilities/FPSGameplayAbility.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

#include "FPSDebugHelper.h"

void UFPSGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (AbilityActivationPolicy == EFPSAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UFPSGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (AbilityActivationPolicy == EFPSAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UFPSAbilitySystemComponent* UFPSGameplayAbility::GetFPSAbilitySystemComponentFromActorInfo() const
{
	return Cast<UFPSAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UPawnCombatComponent* UFPSGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}
