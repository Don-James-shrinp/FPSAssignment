// Origin OvO CopyRight Reserved


#include "Items/Bullets/FPSBulletBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "FPSGameplayTags.h"

#include "FPSDebugHelper.h"
AFPSBulletBase::AFPSBulletBase()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BulletCollisionBox"));
	BulletCollisionBox->SetBoxExtent(FVector(20.f));
	BulletCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(BulletCollisionBox);

	BulletStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletStaticMesh"));
	BulletStaticMesh->SetupAttachment(GetRootComponent());
	

	BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementComponent"));
	BulletMovementComponent->InitialSpeed = 700.f;
	BulletMovementComponent->MaxSpeed = 900.f;
	BulletMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	BulletMovementComponent->ProjectileGravityScale = 0.f;
	BulletMovementComponent->bAutoActivate = false;

	bIsActive = false;
}

void AFPSBulletBase::StartLifeTimer(float Duration)
{
	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ThisClass::Deactivate, Duration, false);
}

void AFPSBulletBase::BeginPlay()
{
	Super::BeginPlay();
	//  绑定碰撞盒的回调函数
	BulletCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	BulletCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void AFPSBulletBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherActor != GetOwner())
	{
		FGameplayEventData Data;
		Data.Instigator = CachedInstigator.Get();
		Data.Target = OtherActor;
		//  子弹发生碰撞
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(  //  将命中事件发送给Shooter，用于后续的处理流程
			CachedInstigator.Get(),
			FPSGameplayTags::Player_Event_Bullet_Hit,
			Data
		);
		//Debug::Print(FString::Printf(TEXT("My Name: %s"), *GetActorNameOrLabel()));
		//Debug::Print(FString::Printf(TEXT("Collisioned Object Name: %s"), *OtherActor->GetActorNameOrLabel()));
		//  将当前命中的子弹回收到对象池
		Deactivate();  //  BUG出在这里，当子弹从对象池中被取出时，会提前发生碰撞导致子弹直接被回收（原因在于子弹会和自己发生碰撞）
	}

}

void AFPSBulletBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//  子弹结束碰撞
}

void AFPSBulletBase::SetActive(bool InIsActive, AActor* InInstigator, FVector StartLocation, FVector Direction)
{
	bIsActive = InIsActive;
	CachedInstigator = InInstigator;

	SetActorHiddenInGame(!bIsActive);  //  设置对象在游戏中的可见性


	//Debug::Print(FString::Printf(TEXT("Active Param: ")) + (InIsActive ? TEXT("True") : TEXT("False")));
	
	if (bIsActive)
	{
		//Debug::Print(TEXT("Activate Bullet Object!"));
		SetActorLocationAndRotation(StartLocation, Direction.Rotation(), false, nullptr, ETeleportType::TeleportPhysics);

		BulletMovementComponent->SetUpdatedComponent(GetRootComponent());
		BulletMovementComponent->Velocity = Direction * BulletMovementComponent->InitialSpeed;
		BulletMovementComponent->Activate(true);

		StartLifeTimer(BulletLifeTime);
	}
	else
	{
		BulletMovementComponent->StopMovementImmediately();
		BulletMovementComponent->Deactivate();

		GetWorldTimerManager().ClearTimer(LifeTimerHandle);

	}
	BulletCollisionBox->SetCollisionEnabled(bIsActive ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);

}

void AFPSBulletBase::Deactivate()
{
	SetActive(false);
}
