// Origin OvO CopyRight Reserved


#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/FPSPlayerWeapon.h"

AFPSPlayerWeapon* UPlayerCombatComponent::GetPlayerWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AFPSPlayerWeapon>(GetCharacterWeaponByTag(InWeaponTag));
}

AFPSPlayerWeapon* UPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<AFPSPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}
