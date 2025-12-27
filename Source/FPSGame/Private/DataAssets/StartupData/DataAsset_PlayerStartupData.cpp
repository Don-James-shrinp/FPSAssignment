// Origin OvO CopyRight Reserved


#include "DataAssets/StartupData/DataAsset_PlayerStartupData.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/FPSGameplayAbility.h"

bool FFPSPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_PlayerStartupData::GiveToAbilitySystemComponent(UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FFPSPlayerAbilitySet& AbilitySet : PlayerStartupAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);  //  给Ability赋予InputTag，使其能够关联起来
		InASCToGive->GiveAbility(AbilitySpec);
	}
}

