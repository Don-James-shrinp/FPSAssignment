// Origin OvO CopyRight Reserved


#include "Characters/FPSEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartupData/DataAsset_EnemyStartupData.h"

#include "FPSDebugHelper.h"
void AFPSEnemyCharacter::PossessedBy(AController* NewController)
{
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
