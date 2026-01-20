// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeaponBase.generated.h"

class UStaticMeshComponent;
class UBulletPoolComponent;

UCLASS()
class FPSGAME_API AFPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSWeaponBase();

	UFUNCTION(BlueprintPure, Category = "Bullet Pool")
	FORCEINLINE UBulletPoolComponent* GetBulletPoolComponent() const { return BulletPoolComponent; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	int32 MaxAmmoNumber = 60;

	UFUNCTION(BlueprintCallable, Category = "FPS|Weapons")
	FORCEINLINE int32 GetCurrentAmmoNumber() const { return CurrentAmmoNumber; }

	UFUNCTION(BlueprintCallable, Category = "FPS|Weapons")
	FORCEINLINE void SetCurrentAmmoNumber(const int32 NewAmmoNumber) { CurrentAmmoNumber = NewAmmoNumber; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBulletPoolComponent* BulletPoolComponent;

	UPROPERTY()
	int32 CurrentAmmoNumber;
};
