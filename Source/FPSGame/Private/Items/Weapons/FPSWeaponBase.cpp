// Origin OvO CopyRight Reserved


#include "Items/Weapons/FPSWeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Characters/FPSEnemyCharacter.h"
#include "Subsystems/FPSBulletPoolWorldSubsystem.h"
#include "Items/Bullets/FPSBulletBase.h"

#include "FPSDebugHelper.h"
// Sets default values
AFPSWeaponBase::AFPSWeaponBase()
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = false;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponStaticMesh);
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

void AFPSWeaponBase::EnemyFire(FVector Location, FVector Direction)
{
	if (!HasAuthority()) return;
	Server_Fire(Location, Direction);
}

void AFPSWeaponBase::RPC_PlayerFire_Implementation(FVector Location, FVector Direction)
{
	Server_Fire(Location, Direction);
}

void AFPSWeaponBase::Server_Fire(FVector Location, FVector Direction)
{
	ConsumeAmmo();  //  消耗弹药，敌人没有弹药限制，玩家有弹药限制

	if (UWorld* World = GetWorld())
	{
		UFPSBulletPoolWorldSubsystem* Pool = World->GetSubsystem<UFPSBulletPoolWorldSubsystem>();
		AFPSBulletBase* Bullet = Pool->GetBullet(BulletClass);

		if (Bullet)
		{
			Bullet->SetActive(true, GetOwner(), Location, Direction);
		}
		else
		{
			Debug::Print(TEXT("Null Bullet"));
		}
	}
}

void AFPSWeaponBase::ConsumeAmmo()
{
	// 派生类即PlayerWeapon需要override此函数来修改弹药数量
}

void AFPSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		UFPSBulletPoolWorldSubsystem* Pool = World->GetSubsystem<UFPSBulletPoolWorldSubsystem>();
		Pool->InitPool(BulletClass, InitialPoolSize);
	}
}

