// Origin OvO CopyRight Reserved


#include "Items/Weapons/FPSPlayerWeapon.h"
#include "AbilitySystem/Abilities/FPSGameplayAbility.h"
#include "Net/UnrealNetwork.h"

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

void AFPSPlayerWeapon::OnRep_CurrentAmmo(int32 OldAmmoNumber)
{

}

void AFPSPlayerWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFPSPlayerWeapon, CurrentAmmoNumber);
}
