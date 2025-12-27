// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupDataBase.generated.h"

class UFPSAbilitySystemComponent;
class UFPSGameplayAbility;
/**
 * 
 */
UCLASS()
class FPSGAME_API UDataAsset_StartupDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);  //  用于将加载的Abilty数据和其他的Startup Data通过ASC给予角色
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UFPSGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UFPSGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UFPSGameplayAbility>>& InAbilitiesToGive, UFPSAbilitySystemComponent* InASCToGive, int32 ApplyLevel);
};
