// Origin OvO CopyRight Reserved


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/FPSWeaponBase.h"
#include "Net/UnrealNetwork.h"

#include "FPSDebugHelper.h"
void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AFPSWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Tag %s already exists! Overwriting."), *InWeaponTagToRegister.ToString());

		CharacterCarriedWeaponMap.Remove(InWeaponTagToRegister);
	}
	
	if (!InWeaponToRegister)
	{
		return;
	}

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

AFPSWeaponBase* UPawnCombatComponent::GetCharacterWeaponByTag(FGameplayTag InWeaponTag) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTag))
	{
		if (AFPSWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTag))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AFPSWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::OnRep_CurrentEquippedWeaponTag(FGameplayTag OldWeaponTag)
{
}

void UPawnCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(UPawnCombatComponent, CurrentEquippedWeaponTag);
}
