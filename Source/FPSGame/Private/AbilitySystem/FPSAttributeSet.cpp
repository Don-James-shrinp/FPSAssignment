// Origin OvO CopyRight Reserved


#include "AbilitySystem/FPSAttributeSet.h"

UFPSAttributeSet::UFPSAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
}

void UFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

}
