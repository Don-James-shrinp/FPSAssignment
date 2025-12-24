// Origin OvO CopyRight Reserved


#include "Items/Weapons/FPSWeaponBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSWeaponBase::AFPSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponStaticMesh);
}

