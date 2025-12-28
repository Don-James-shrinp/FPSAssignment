// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class AFPSPlayerWeapon;
/**
 * 
 */
UCLASS()
class FPSGAME_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	AFPSPlayerWeapon* GetPlayerWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	AFPSPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;
};
