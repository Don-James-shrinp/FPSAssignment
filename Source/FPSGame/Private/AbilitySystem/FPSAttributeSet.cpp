// Origin OvO CopyRight Reserved


#include "AbilitySystem/FPSAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "FPSBlueprintFunctionLibrary.h"
#include "FPSGameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "PlayerState/FPSPlayerState.h"
#include "Characters/FPSPlayerCharacter.h"

#include "FPSDebugHelper.h"
UFPSAttributeSet::UFPSAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitDefensePower(1.f);
}

void UFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())  //  受到伤害后，需要更新CurrentHealth
	{
		const float NewHealth = FMath::Max(GetCurrentHealth() - GetDamageTaken(), 0.f);
		SetCurrentHealth(NewHealth);
		if (GetCurrentHealth() == 0.f)  //  遭受伤害之后，生命值归零，进行击杀判定
		{
			FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
			if (AFPSPlayerCharacter* Instigator = Cast<AFPSPlayerCharacter>(Context.GetInstigator()))  //  造成伤害的是玩家时才需要判定
			{
				AFPSPlayerState* PlayerState = Instigator->GetPlayerState<AFPSPlayerState>();
				if (PlayerState)
				{
					PlayerState->AddKillCount(1);
				}
			}
		}
	}

	if (GetCurrentHealth() == 0.f)
	{
		UFPSBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(
			Data.Target.GetAvatarActor(),
			FPSGameplayTags::Shared_Status_Dead
		);
	}
}

void UFPSAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UFPSAttributeSet, CurrentHealth);
	DOREPLIFETIME(UFPSAttributeSet, MaxHealth);
	DOREPLIFETIME(UFPSAttributeSet, DefensePower);
	DOREPLIFETIME(UFPSAttributeSet, DamageTaken);
}

void UFPSAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSAttributeSet, CurrentHealth, OldHealth);

	AActor* AvatarActor = GetOwningActor();
	if (!AvatarActor) return;

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(AvatarActor))
	{
		if (UPawnUIComponent* PawnUIComponent = PawnUIInterface->GetPawnUIComponent())
		{
			// 更新 UI
			PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		}
	}
}
