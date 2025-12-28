// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/FPSWeaponBase.h"
#include "FPSTypes/FPSStructTypes.h"
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
};
