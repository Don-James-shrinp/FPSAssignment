// Origin OvO CopyRight Reserved


#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/FPSPlayerWeapon.h"
#include "Characters/FPSPlayerCharacter.h"

#include "FPSDebugHelper.h"
AFPSPlayerWeapon* UPlayerCombatComponent::GetPlayerWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AFPSPlayerWeapon>(GetCharacterWeaponByTag(InWeaponTag));
}

AFPSPlayerWeapon* UPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<AFPSPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UPlayerCombatComponent::GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
    return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UPlayerCombatComponent::OnRep_CurrentEquippedWeaponTag(FGameplayTag OldWeaponTag)
{
    Debug::Print(TEXT("Tag Replicated!"));
    AFPSPlayerWeapon* CurrentEquippedWeapon = GetPlayerCurrentEquippedWeapon();
    FAttachmentTransformRules AttachmentTransformRules(
        EAttachmentRule::SnapToTarget,
        EAttachmentRule::KeepRelative,
        EAttachmentRule::KeepWorld,
        false);
    if (CurrentEquippedWeapon)
    {
        CurrentEquippedWeapon->AttachToComponent(
            GetOwningPawn<ACharacter>()->GetMesh(),
            AttachmentTransformRules,
            GunHoldSocket
        );
    }
}
