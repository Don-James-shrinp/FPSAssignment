// Origin OvO CopyRight Reserved


#include "DataAssets/Input/DataAsset_InputConfig.h"

TObjectPtr<UInputAction> UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
    for (const FFPSInputActionConfig& InputActionConfig : NativeInputActions)
    {
        if (!InputActionConfig.IsValid()) continue;

        if (InputActionConfig.InputTag == InInputTag)
        {
            return InputActionConfig.InputAction;
        }
    }
    return TObjectPtr<UInputAction>();
}
