// Origin OvO CopyRight Reserved

#pragma once
#include "GameplayTagContainer.h"
#include "FPSStructTypes.generated.h"
class UFPSGameplayAbility;
class UFPSPlayerLinkedAnimLayer;
class UInputMappingContext;
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

USTRUCT(BlueprintType)
struct FFPSPlayerWeaponData  //  武器附属的数据（AnimLayer和Ability等）
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFPSPlayerLinkedAnimLayer> WeaponAnimLayerToLink;  //  装备武器后需要Link的AnimLayer

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FFPSPlayerAbilitySet> DefaultWeaponAbilities;  //  装备武器后获得的能力
};