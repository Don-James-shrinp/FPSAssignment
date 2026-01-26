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

public:
	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	AFPSPlayerWeapon* GetPlayerWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	AFPSPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	float GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	virtual void OnRep_CurrentEquippedWeaponTag(FGameplayTag OldWeaponTag) override;

	UPROPERTY(EditDefaultsOnly, Category = "FPS|Combat")
	FName GunHoldSocket = FName(TEXT("Hold_Gun_Socket"));
};
