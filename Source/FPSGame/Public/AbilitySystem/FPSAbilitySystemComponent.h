// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FPSTypes/FPSStructTypes.h"
#include "FPSAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);  //  用于激活(activate)那些由输入触发的Ability的输入事件处理函数
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "FPS|Ability")
	void GrantWeaponAbilities(const TArray<FFPSPlayerAbilitySet>& InWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);  //  装备武器时，将武器附属的能力授予角色，并返回SpecHandle用于在Remove时使用

	UFUNCTION(BlueprintCallable, Category = "FPS|Ability")
	void RemoveGrantedAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);  //  普通引用在蓝图中默认为Out Parameter，通过UPARAM(ref)使其成为input pin
	
};
