// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletPoolComponent.generated.h"

class AFPSBulletBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UBulletPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletPoolComponent();

	UPROPERTY(EditDefaultsOnly, Category = "BulletPool Config")
	TSubclassOf<AFPSBulletBase> BulletClass;  //  子弹类

	UPROPERTY(EditDefaultsOnly, Category = "BulletPool Config")
	int32 BulletPoolSize = 30;  //  对象池的初始容量

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
