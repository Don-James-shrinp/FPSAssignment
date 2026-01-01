// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/FPSGameplayAbility.h"
#include "FPSPlayerGameplayAbility.generated.h"

class AFPSPlayerCharacter;
class AFPSPlayerController;
class UPlayerUIComponent;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSPlayerGameplayAbility : public UFPSGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "FPS|Ability")
	AFPSPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "FPS|Ability")
	AFPSPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "FPS|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "FPS|Ability")
	UPlayerUIComponent* GetPlayerUIComponentFromActorInfo();

private:
	TWeakObjectPtr<AFPSPlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<AFPSPlayerController> CachedPlayerController;
};
