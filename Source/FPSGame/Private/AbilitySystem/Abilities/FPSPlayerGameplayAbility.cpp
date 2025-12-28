// Origin OvO CopyRight Reserved


#include "AbilitySystem/Abilities/FPSPlayerGameplayAbility.h"
#include "Characters/FPSPlayerCharacter.h"
#include "Controllers/FPSPlayerController.h"
#include "Components/Combat/PlayerCombatComponent.h"
AFPSPlayerCharacter* UFPSPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
    if (!CachedPlayerCharacter.IsValid())
    {
        CachedPlayerCharacter = Cast<AFPSPlayerCharacter>(GetAvatarActorFromActorInfo());
    }
    return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

AFPSPlayerController* UFPSPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
    if (!CachedPlayerController.IsValid())
    {
        CachedPlayerController = Cast<AFPSPlayerController>(CurrentActorInfo->PlayerController);
    }
    return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UFPSPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
    return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
