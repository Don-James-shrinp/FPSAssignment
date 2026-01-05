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

	UFUNCTION(BlueprintCallable, Category = "FPS|Bullets")
	void SetActive(bool InIsActive, AActor* InInstigator = nullptr, FVector StartLocation = FVector::ZeroVector, FVector Direction = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable, Category = "FPS|Bullets")
	FORCEINLINE bool IsActive() const { return bIsActive; }

	UFUNCTION(BlueprintCallable, Category = "FPS|Bullets")
	void StartLifeTimer(float Duration);  //  设置生命周期定时器，当定时结束后就会回收该对象

	UPROPERTY(EditDefaultsOnly, Category = "Bullets")
	float BulletLifeTime = 10.f;  //  子弹的生命周期

protected:
	void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullets")
	UStaticMeshComponent* BulletStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullets")
	UBoxComponent* BulletCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullets")
	UProjectileMovementComponent* BulletMovementComponent;

	UFUNCTION()
	void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsActive;  //  当前子弹是否处于Active状态，如果是false表示当前子弹对象处于空闲状态，可以被使用
	FTimerHandle LifeTimerHandle;
	TWeakObjectPtr<AActor> CachedInstigator;  //  将子弹发射出去动作的执行者(Shooter)

	void Deactivate();  //  对象的回收逻辑，定时将子弹对象回收到对象池中
};
