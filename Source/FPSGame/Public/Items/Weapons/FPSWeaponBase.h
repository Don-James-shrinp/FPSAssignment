// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
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

	virtual void OnRep_Owner() override;  //  Owner从服务器同步到客户端时客户端调用

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	FGameplayTag WeaponTag;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBulletPoolComponent* BulletPoolComponent;
};
