// Origin OvO CopyRight Reserved


#include "Characters/FPSEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartupData/DataAsset_EnemyStartupData.h"
#include "Components/UI/EnemyUIComponent.h"

#include "FPSDebugHelper.h"
AFPSEnemyCharacter::AFPSEnemyCharacter()
{
	EnemyPawnUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyPawnUIComponent"));
}

UPawnUIComponent* AFPSEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyPawnUIComponent;
}

UEnemyUIComponent* AFPSEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyPawnUIComponent;
}

void AFPSEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);  //  BUG产生的原因，没有调用基类的PossessedBy，导致ASC没有初始化
	InitStartupData();
}

void AFPSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
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
					Debug::Print(TEXT("Enemy Data Loaded!"));
					LoadedData->GiveToAbilitySystemComponent(FPSAbilitySystemComponent, AbilityLevel);
				}
			}
		)
	);
}
