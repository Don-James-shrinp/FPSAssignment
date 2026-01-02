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
	
	if (!StartupGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartupGameplayEffects)  //  将StartupEffect Apply到自身
		{
			if (!EffectClass)
			{
				continue;
			}
			UGameplayEffect* EffectClassDefaultObject = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(
				EffectClassDefaultObject,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
}

void UDataAsset_StartupDataBase::GrantAbilities(const TArray<TSubclassOf<UFPSGameplayAbility>>& InAbilitiesToGive, UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<UFPSGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			return;
		}
		FGameplayAbilitySpec AbilitySpec(Ability);  //  Bug在这里，初始化的时候没有用Ability作为参数进行初始化，而是使用的默认初始化
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();  //  这是ASC的初始化信息，在Character中被赋予这些信息
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
