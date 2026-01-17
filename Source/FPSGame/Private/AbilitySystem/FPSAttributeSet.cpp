// Origin OvO CopyRight Reserved


#include "AbilitySystem/FPSAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "FPSBlueprintFunctionLibrary.h"
#include "FPSGameplayTags.h"

#include "FPSDebugHelper.h"
UFPSAttributeSet::UFPSAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitDefensePower(1.f);
}

void UFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())  //  生命值发生变化之后，需要通过PawnUIComponent对Delegate进行Broadcast
	{
		const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())  //  受到伤害后，需要更新CurrentHealth
	{
		const float NewHealth = FMath::Max(GetCurrentHealth() - GetDamageTaken(), 0.f);
		SetCurrentHealth(NewHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (GetCurrentHealth() == 0.f)
	{
		UFPSBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(
			Data.Target.GetAvatarActor(),
			FPSGameplayTags::Shared_Status_Dead
		);
	}
}
