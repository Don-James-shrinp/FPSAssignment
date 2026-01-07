// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "DataAsset_EnemyStartupData.generated.h"

class UFPSEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class FPSGAME_API UDataAsset_EnemyStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartupData")
	TArray<TSubclassOf<UFPSEnemyGameplayAbility>> EnemyCombatAbilities;
};
