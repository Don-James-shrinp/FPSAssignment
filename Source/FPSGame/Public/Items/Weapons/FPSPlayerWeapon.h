// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/FPSWeaponBase.h"
#include "FPSTypes/FPSStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "FPSPlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerWeapon : public AFPSWeaponBase
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FFPSPlayerWeaponData PlayerWeaponData;

	UFUNCTION(BlueprintCallable, Category = "FPS|Ability")
	void SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;  // GrantedAbilitySpecHandles Getter
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
