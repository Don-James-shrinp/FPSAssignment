// Origin OvO CopyRight Reserved


#include "Components/ObjectPool/BulletPoolComponent.h"
#include "Items/Bullets/FPSBulletBase.h"

#include "FPSDebugHelper.h"
UBulletPoolComponent::UBulletPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}

AFPSBulletBase* UBulletPoolComponent::GetBulletFromPool(int32& OutIndex)
{
	int32 index = 0;
	for (AFPSBulletBase* Bullet : BulletPool)  //  现在的复杂度为O(n)，这里可以优化，设计一个类似于大根堆的数据结构，非激活状态的值为1，激活状态为0，每次取元素只需要取堆顶元素
	{
		if (Bullet && !Bullet->IsActive())
		{
			OutIndex = index;
			return Bullet;
		}
		index++;
	}

	//  这里处理没有空闲的子弹对象的情况，需要对对象池进行动态扩容
	if (BulletClass)
	{
		AFPSBulletBase* NewBullet = GetWorld()->SpawnActor<AFPSBulletBase>(BulletClass);
		if (NewBullet)
		{
			NewBullet->SetActive(false);
			OutIndex = BulletPool.AddUnique(NewBullet);
			return NewBullet;
		}
	}
	return nullptr;
}

AFPSBulletBase* UBulletPoolComponent::GetBulletByIndex(int32 OutIndex)
{
	return BulletPool[OutIndex];
}


void UBulletPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(BulletClass, TEXT("Forgot to assign bullet class in bullet pool!"))

	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < BulletPoolSize; i++)
		{
			FVector SpawnLocation = FVector(0.f, 0.f, 0.f);
			FRotator SpawnRotation = FRotator::ZeroRotator;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetOwner()->GetInstigator();

			AFPSBulletBase* NewBullet = World->SpawnActor<AFPSBulletBase>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (NewBullet)
			{
				NewBullet->SetActive(false);
				BulletPool.AddUnique(NewBullet);
			}
		}
	}

		
}