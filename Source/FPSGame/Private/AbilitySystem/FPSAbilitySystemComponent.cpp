// Origin OvO CopyRight Reserved


#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/FPSPlayerGameplayAbility.h"

#include "FPSDebugHelper.h"
void UFPSAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())  //  传入的GameplayTag无效
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())  //  遍历所有可激活的Abilty，然后找到与传入的Input Tag对应的对应的Ability
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UFPSAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UFPSAbilitySystemComponent::GrantWeaponAbilities(const TArray<FFPSPlayerAbilitySet>& InWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	for (const FFPSPlayerAbilitySet& AbilitySet : InWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UFPSAbilitySystemComponent::RemoveGrantedAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (!SpecHandle.IsValid())
		{
			continue;
		}
		Debug::Print(TEXT("Removed!"));
		ClearAbility(SpecHandle);
	}

	InSpecHandlesToRemove.Empty();
}
