// Origin OvO CopyRight Reserved


#include "AbilitySystem/Abilities/FPSPlayerGameplayAbility.h"
#include "Characters/FPSPlayerCharacter.h"
#include "Controllers/FPSPlayerController.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "FPSGameplayTags.h"
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
    // 1. 如果缓存有效，直接返回
    if (CachedPlayerController.IsValid())
    {
        return CachedPlayerController.Get();
    }

    // 2. 尝试从 ActorInfo 获取 (GAS 默认缓存)
    if (CurrentActorInfo->PlayerController.IsValid())
    {
        CachedPlayerController = Cast<AFPSPlayerController>(CurrentActorInfo->PlayerController.Get());
    }

    // 3. [关键修复] 如果 ActorInfo 里没存 (通常是因为 Init 时机太早)，则从 AvatarActor 身上现找
    if (!CachedPlayerController.IsValid() && CurrentActorInfo->AvatarActor.IsValid())
    {
        // 将 Avatar 转为 Pawn
        if (APawn* AvatarPawn = Cast<APawn>(CurrentActorInfo->AvatarActor.Get()))
        {
            // 获取 Pawn 当前持有的 Controller
            CachedPlayerController = Cast<AFPSPlayerController>(AvatarPawn->GetController());
        }
    }

    return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UFPSPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
    return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

UPlayerUIComponent* UFPSPlayerGameplayAbility::GetPlayerUIComponentFromActorInfo()
{
    return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}