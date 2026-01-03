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
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FFPSPlayerWeaponData PlayerWeaponData;

	UFUNCTION(BlueprintCallable, Category = "FPS|Ability")
	void SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;  // GrantedAbilitySpecHandles Getter

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	int32 MaxAmmoNumber = 60;  //  最大弹药数量

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	
	UFUNCTION(BlueprintCallable, Category = "FPS|Weapons")
	FORCEINLINE int32 GetCurrentAmmoNumber() const { return CurrentAmmoNumber; }

	UFUNCTION(BlueprintCallable, Category = "FPS|Weapons")
	void SetCurrentAmmoNumber(const int32 NewAmmoNumber);
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

	int32 CurrentAmmoNumber;  //  现在的子弹数量
};
