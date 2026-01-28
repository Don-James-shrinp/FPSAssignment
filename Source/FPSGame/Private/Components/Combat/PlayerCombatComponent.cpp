// Origin OvO CopyRight Reserved


#include "Components/Combat/PlayerCombatComponent.h"
#include "Items/Weapons/FPSPlayerWeapon.h"
#include "Characters/FPSPlayerCharacter.h"
#include "AnimInstances/Player/FPSPlayerLinkedAnimLayer.h"

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

void UPlayerCombatComponent::OnRep_CurrentEquippedWeaponTag(FGameplayTag OldCurrentEquippedWeaponTag)
{
    Debug::Print(TEXT("Rep Tag"));
    ACharacter* OwnerCharacter = GetOwner<ACharacter>();
    
    if (CurrentEquippedWeaponTag.IsValid())
    {
        TSubclassOf<UAnimInstance> AnimLayerToLink = GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponAnimLayerToLink;
        //  Link Anim Layer
        if (OwnerCharacter)
        {
            OwnerCharacter->GetMesh()->LinkAnimClassLayers(AnimLayerToLink);
        }

    }
    else
    {
        // Unlink Anim Layer
        TSubclassOf<UAnimInstance> AnimLayerToUnlink = GetPlayerWeaponByTag(OldCurrentEquippedWeaponTag)->PlayerWeaponData.WeaponAnimLayerToLink;
        if (OwnerCharacter)
        {
            OwnerCharacter->GetMesh()->UnlinkAnimClassLayers(AnimLayerToUnlink);
        }
    }
}
