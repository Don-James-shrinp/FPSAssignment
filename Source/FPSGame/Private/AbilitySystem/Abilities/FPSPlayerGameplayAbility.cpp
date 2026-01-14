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

UPlayerUIComponent* UFPSPlayerGameplayAbility::GetPlayerUIComponentFromActorInfo()
{
    return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}

FGameplayEffectSpecHandle UFPSPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponDamage)
{
    check(EffectClass);
    
    FGameplayEffectContextHandle ContextHandle = GetFPSAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle EffectSpecHandle = GetFPSAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );

    EffectSpecHandle.Data->SetSetByCallerMagnitude(  //  设定SetByCallerMagnitude，向TMap<FGameplayTag, float>中传入武器的伤害
        FPSGameplayTags::Shared_SetByCaller_WeaponBaseDamage_Rifle,
        InWeaponDamage
    );

    return EffectSpecHandle;
}
