// Origin OvO CopyRight Reserved


#include "Items/Weapons/FPSWeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ObjectPool/BulletPoolComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Characters/FPSEnemyCharacter.h"

#include "FPSDebugHelper.h"
// Sets default values
AFPSWeaponBase::AFPSWeaponBase()
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = false;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponStaticMesh);

	BulletPoolComponent = CreateDefaultSubobject<UBulletPoolComponent>(TEXT("BulletPoolComponent"));
}

void AFPSWeaponBase::OnRep_Owner()
{
	Super::OnRep_Owner();

	if (GetOwner())
	{
		if (UPawnCombatComponent* CombatComp = GetOwner()->FindComponentByClass<UPawnCombatComponent>())
		{
			bool bRegisterAsEquippedWeapon = false;
			if (Cast<AFPSEnemyCharacter>(GetOwner()))
			{
				bRegisterAsEquippedWeapon = true;
			}
			CombatComp->RegisterSpawnedWeapon(WeaponTag, this, bRegisterAsEquippedWeapon);
		}
	}
}

