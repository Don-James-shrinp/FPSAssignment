// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_PlayerStartupData.generated.h"

class UFPSPlayerGameplayAbility;
class UFPSGameplayAbility;
/**
 * 
 */

USTRUCT(BlueprintType)
struct FFPSPlayerAbilitySet  //  将Input_Tag和Ability关联起来的数据结构，用于实现使用某种Input来激活Ability的激活策略(On Triggered)
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFPSGameplayAbility> AbilityToGrant;

	bool IsValid() const;

};

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
