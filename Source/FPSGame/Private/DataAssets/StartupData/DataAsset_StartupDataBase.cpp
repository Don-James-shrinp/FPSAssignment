// Origin OvO CopyRight Reserved


#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/FPSGameplayAbility.h"

#include "FPSDebugHelper.h"
void UDataAsset_StartupDataBase::GiveToAbilitySystemComponent(UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	

	//  将能力通过ASC给予角色
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartupDataBase::GrantAbilities(const TArray<TSubclassOf<UFPSGameplayAbility>>& InAbilitiesToGive, UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<UFPSGameplayAbility> &Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			return;
		}
		Debug::Print(TEXT("Ability Granted!"));

		FGameplayAbilitySpec AbilitySpec;
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();  //  这是ASC的初始化信息，在Character中被赋予这些信息
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
