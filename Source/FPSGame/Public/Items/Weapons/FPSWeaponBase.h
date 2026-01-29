// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "FPSWeaponBase.generated.h"

class UStaticMeshComponent;
class UBulletPoolComponent;
class AFPSBulletBase;

UCLASS()
class FPSGAME_API AFPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSWeaponBase();

	virtual void OnRep_Owner() override;  //  Owner从服务器同步到客户端时客户端调用

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	FGameplayTag WeaponTag;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AFPSBulletBase> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	int32 InitialPoolSize = 30;

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void EnemyFire(FVector Location, FVector Direction);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RPC_PlayerFire(FVector Location, FVector Direction);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponStaticMesh;

	void Server_Fire(FVector Location, FVector Direction);

	virtual void ConsumeAmmo();

	virtual void BeginPlay() override;
};
