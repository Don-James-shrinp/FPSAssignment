// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FPSBulletPoolWorldSubsystem.generated.h"

class AFPSBulletBase;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSBulletPoolWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	void InitPool(TSubclassOf<AFPSBulletBase> BulletClass, int32 Count);

	AFPSBulletBase* GetBullet(TSubclassOf<AFPSBulletBase> BulletClass);

	void ReturnBullet(AFPSBulletBase* Bullet);

private:
	TArray<AFPSBulletBase*> BulletPool;
};
