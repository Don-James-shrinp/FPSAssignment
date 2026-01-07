// Origin OvO CopyRight Reserved


#include "DataAssets/StartupData/DataAsset_EnemyStartupData.h"
#include "AbilitySystem/Abilities/FPSEnemyGameplayAbility.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
void UDataAsset_EnemyStartupData::GiveToAbilitySystemComponent(UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	for (TSubclassOf<UFPSEnemyGameplayAbility>& EnemyAbility : EnemyCombatAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(EnemyAbility);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
