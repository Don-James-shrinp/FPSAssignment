// Origin OvO CopyRight Reserved


#include "AbilitySystem/Abilities/FPSEnemyGameplayAbility.h"
#include "Characters/FPSEnemyCharacter.h"

AFPSEnemyCharacter* UFPSEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AFPSEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.Get();
}
