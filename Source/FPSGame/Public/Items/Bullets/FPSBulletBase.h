// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBulletBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UProjectileMovementComponent;
UCLASS()
class FPSGAME_API AFPSBulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSBulletBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullets")
	TObjectPtr<UStaticMeshComponent> BulletStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullets")
	TObjectPtr<UBoxComponent> BulletCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullets")
	TObjectPtr<UProjectileMovementComponent> BulletMovementComponent;

	UFUNCTION()
	void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
