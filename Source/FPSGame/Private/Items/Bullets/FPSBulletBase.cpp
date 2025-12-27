// Origin OvO CopyRight Reserved


#include "Items/Bullets/FPSBulletBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFPSBulletBase::AFPSBulletBase()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BulletCollisionBox"));
	BulletCollisionBox->SetupAttachment(GetRootComponent());
	BulletCollisionBox->SetBoxExtent(FVector(20.f));
	BulletCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(BulletCollisionBox);

	BulletStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletStaticMesh"));
	BulletStaticMesh->SetupAttachment(GetRootComponent());
	//  绑定碰撞盒的回调函数
	BulletCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	BulletCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);

	BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementComponent"));
	BulletMovementComponent->InitialSpeed = 700.f;
	BulletMovementComponent->MaxSpeed = 900.f;
	BulletMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	BulletMovementComponent->ProjectileGravityScale = 0.f;
}

void AFPSBulletBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//  子弹发生碰撞
}

void AFPSBulletBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//  子弹结束碰撞
}
