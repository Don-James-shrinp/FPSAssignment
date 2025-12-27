// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
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
	
};
