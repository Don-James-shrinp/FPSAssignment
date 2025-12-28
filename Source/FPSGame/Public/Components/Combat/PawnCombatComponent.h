// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/FPSPawnExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AFPSWeaponBase;
/**
 * 
 */
UCLASS()
class FPSGAME_API UPawnCombatComponent : public UFPSPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AFPSWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	AFPSWeaponBase* GetCharacterWeaponByTag(FGameplayTag InWeaponTag) const;

	UPROPERTY(BlueprintReadWrite, Category = "FPS|Combat")
	FGameplayTag CurrentEquippedWeaponTag;  //  现在装备的武器Tag

	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	AFPSWeaponBase* GetCharacterCurrentEquippedWeapon() const;

private:
	TMap<FGameplayTag, AFPSWeaponBase*> CharacterCarriedWeaponMap;
};
