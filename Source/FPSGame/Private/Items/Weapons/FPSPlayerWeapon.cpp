// Origin OvO CopyRight Reserved


#include "Items/Weapons/FPSPlayerWeapon.h"
#include "AbilitySystem/Abilities/FPSGameplayAbility.h"

void AFPSPlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmoNumber = MaxAmmoNumber;
}

void AFPSPlayerWeapon::SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AFPSPlayerWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}

void AFPSPlayerWeapon::SetCurrentAmmoNumber(const int32 NewAmmoNumber)
{
	CurrentAmmoNumber = NewAmmoNumber;
}
