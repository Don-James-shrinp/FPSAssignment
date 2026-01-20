// Origin OvO CopyRight Reserved


#include "Characters/FPSEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartupData/DataAsset_EnemyStartupData.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/FPSWidgetBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

#include "FPSDebugHelper.h"
AFPSEnemyCharacter::AFPSEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;  //  将朝向改变为移动方向
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;


	EnemyPawnUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyPawnUIComponent"));

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidget"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

	EnemyCombatComponent = CreateDefaultSubobject<UPawnCombatComponent>(TEXT("EnemyCombatComponent"));
}

UPawnUIComponent* AFPSEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyPawnUIComponent;
}

UEnemyUIComponent* AFPSEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyPawnUIComponent;
}

UPawnCombatComponent* AFPSEnemyCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

void AFPSEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);  //  BUG产生的原因，没有调用基类的PossessedBy，导致ASC没有初始化
	InitStartupData();
}

void AFPSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UFPSWidgetBase* HealthWidget = Cast<UFPSWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AFPSEnemyCharacter::InitStartupData()
{
	if (CharacterStartupData.IsNull())
	{
		return;
	}

	int32 AbilityLevel = 1;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, AbilityLevel]
			{
				if (UDataAsset_StartupDataBase* LoadedData = CharacterStartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(FPSAbilitySystemComponent, AbilityLevel);
				}
			}
		)
	);
}
