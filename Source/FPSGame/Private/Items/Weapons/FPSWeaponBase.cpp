// Origin OvO CopyRight Reserved


#include "Items/Weapons/FPSWeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ObjectPool/BulletPoolComponent.h"

// Sets default values
AFPSWeaponBase::AFPSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponStaticMesh);

	BulletPoolComponent = CreateDefaultSubobject<UBulletPoolComponent>(TEXT("BulletPoolComponent"));
}

