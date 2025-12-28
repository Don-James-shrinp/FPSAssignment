// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "FPSTypes/FPSStructTypes.h"
#include "DataAsset_PlayerStartupData.generated.h"

/**
 * 
 */



UCLASS()
class FPSGAME_API UDataAsset_PlayerStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;  //  派生类负责处理当前类新增的Ability的给予
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartupData")
	TArray<FFPSPlayerAbilitySet> PlayerStartupAbilities;
};
