// Origin OvO CopyRight Reserved

#include "FPSTypes/FPSStructTypes.h"
#include "AbilitySystem/Abilities/FPSGameplayAbility.h"

bool FFPSPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}