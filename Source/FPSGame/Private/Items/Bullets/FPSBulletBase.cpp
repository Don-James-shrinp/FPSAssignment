// Origin OvO CopyRight Reserved


#include "Items/Bullets/FPSBulletBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "FPSGameplayTags.h"
#include "Characters/FPSEnemyCharacter.h"
#include "Characters/FPSPlayerCharacter.h"

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
    bReplicates = true;
    SetReplicateMovement(true);
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
    if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
    {
        return;
    }

    if (OtherActor->IsA(AFPSBulletBase::StaticClass()))
    {
        return;
    }


    if (!HasAuthority())
    {
        return;
    }


    if (CachedInstigator.IsValid()) // 确保 CachedInstigator 没死/没被销毁
    {
        AFPSPlayerCharacter* PlayerCharacter = Cast<AFPSPlayerCharacter>(CachedInstigator.Get());        
        FGameplayEventData Data;
        Data.Instigator = CachedInstigator.Get();
        Data.Target = OtherActor; // 记录被打中的人
        Data.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(OtherActor); // 推荐携带 TargetData

        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
            CachedInstigator.Get(),
            FPSGameplayTags::Shared_Event_Bullet_Hit,
            Data
        );
    }

    Deactivate();

}

void AFPSBulletBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//  子弹结束碰撞
}

void AFPSBulletBase::SetActive(bool InIsActive, AActor* InInstigator, FVector StartLocation, FVector Direction)
{
    bIsActive = InIsActive;
    CachedInstigator = InInstigator; // 保存 Instigator，用于后续发送 Event

    // 1. 设置 Owner (GAS 和 网络同步的关键)
    // 如果不设置 Owner，GetOwner() 会返回空，你的碰撞代码里 OtherActor != GetOwner() 判定就会失效
    if (InInstigator)
    {
        SetOwner(InInstigator);
    }

    SetActorHiddenInGame(!bIsActive);

    if (bIsActive)
    {
        // 【重要修正 1】: 在开启碰撞和移动之前，强制忽略射击者
        if (BulletCollisionBox && InInstigator)
        {
            // 方法 A: 告诉碰撞组件忽略射击者
            BulletCollisionBox->IgnoreActorWhenMoving(InInstigator, true);

            // 方法 B: 同样添加到移动组件的忽略列表 (双重保险)
            BulletCollisionBox->MoveIgnoreActors.Add(InInstigator);
        }

        // 2. 瞬移位置 (你原本写得很好)
        SetActorLocationAndRotation(StartLocation, Direction.Rotation(), false, nullptr, ETeleportType::TeleportPhysics);

        // 【优化建议】: 子弹通常只需要 Query (检测重叠)，不需要 Physics (物理模拟/受重力翻滚)
        // 除非你的子弹是手雷或者需要物理反弹，否则用 QueryOnly 性能更好
        BulletCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

        // 3. 激活移动组件
        BulletMovementComponent->SetUpdatedComponent(GetRootComponent());
        BulletMovementComponent->Velocity = Direction * BulletMovementComponent->InitialSpeed;
        BulletMovementComponent->Activate(true);

        StartLifeTimer(BulletLifeTime);
    }
    else
    {
        // --- 停用逻辑 ---

        // 【清理工作】: 归还池子时，清除忽略列表，防止下次给别人用时还忽略上一个人
        if (BulletCollisionBox)
        {
            BulletCollisionBox->MoveIgnoreActors.Empty();
            BulletCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }

        BulletMovementComponent->StopMovementImmediately();
        BulletMovementComponent->Deactivate();

        GetWorldTimerManager().ClearTimer(LifeTimerHandle);

        // 清空 Owner，断开引用
        SetOwner(nullptr);
    }

}

void AFPSBulletBase::Deactivate()
{
	SetActive(false);
}
