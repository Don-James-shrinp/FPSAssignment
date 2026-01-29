// Origin OvO CopyRight Reserved


#include "Subsystems/FPSBulletPoolWorldSubsystem.h"
#include "Items/Bullets/FPSBulletBase.h"

#include "FPSDebugHelper.h"
void UFPSBulletPoolWorldSubsystem::InitPool(TSubclassOf<AFPSBulletBase> BulletClass, int32 Count)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	if (!BulletClass) return;

	int32 CurrentNum = BulletPool.Num();

	if (CurrentNum >= Count)
	{
		return;
	}

	int32 Needed = Count - CurrentNum;

	for (int32 i = 0; i < Needed; i++)
	{
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FVector SpawnLocation = FVector(0.f, 0.f, 0.f);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AFPSBulletBase* NewBullet = GetWorld()->SpawnActor<AFPSBulletBase>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (NewBullet)
		{
			NewBullet->SetReplicates(true);
			NewBullet->SetReplicateMovement(true);
			NewBullet->SetActive(false);
			BulletPool.Add(NewBullet);
		}

	}

}

AFPSBulletBase* UFPSBulletPoolWorldSubsystem::GetBullet(TSubclassOf<AFPSBulletBase> BulletClass)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return nullptr;  //  服务端调用

	AFPSBulletBase* SelectedBullet = nullptr;
	while (BulletPool.Num() > 0)
	{
		AFPSBulletBase* Bullet = BulletPool.Pop();

		if (IsValid(Bullet))
		{
			SelectedBullet = Bullet;
			break;
		}
	}

	if (!SelectedBullet)  //  对象池中没有可用的对象
	{
		FActorSpawnParameters SpawnParams;
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FVector SpawnLocation = FVector(0.f, 0.f, 0.f);
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AFPSBulletBase* NewBullet = GetWorld()->SpawnActor<AFPSBulletBase>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (NewBullet)
		{
			NewBullet->SetReplicates(true);
			NewBullet->SetReplicateMovement(true);
			NewBullet->SetActive(false);
			SelectedBullet = NewBullet;
		}
	}

	return SelectedBullet;
}

void UFPSBulletPoolWorldSubsystem::ReturnBullet(AFPSBulletBase* Bullet)
{
	Bullet->SetActive(false);

	BulletPool.Add(Bullet);
}
