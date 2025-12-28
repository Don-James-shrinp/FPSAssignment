// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "FPSInputComponent.generated.h"

class UDataAsset_InputConfig;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <typename UserObject, typename CallbackFunc>
	void BindNativeInputAction(
		const UDataAsset_InputConfig* InInputConfig,
		const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent,
		UserObject* ContextObject,
		CallbackFunc Func);

	template <typename UserObject, typename CallbackFunc>
	void BindAbilityInputAction(
		const UDataAsset_InputConfig* InInputConfig,
		UserObject* ContextObject,
		CallbackFunc InputPressedFunc,
		CallbackFunc InputReleasedFunc
	);
};

template <typename UserObject, typename CallbackFunc>
void UFPSInputComponent::BindNativeInputAction(
	const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag,
	ETriggerEvent TriggerEvent,
	UserObject* ContextObject,
	CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("没有给定Input Config Data"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);  //  为InputAction绑定事件处理函数
	}
}

template<typename UserObject, typename CallbackFunc>
inline void UFPSInputComponent::BindAbilityInputAction(
	const UDataAsset_InputConfig* InInputConfig, 
	UserObject* ContextObject, 
	CallbackFunc InputPressedFunc, 
	CallbackFunc InputReleasedFunc)
{
	for (const FFPSInputActionConfig& InputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!InputActionConfig.IsValid())
		{
			continue;
		}
		BindAction(InputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc);
		BindAction(InputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc);
	}
}
