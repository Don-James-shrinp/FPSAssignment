// Origin OvO CopyRight Reserved


#include "Components/UI/PlayerUIComponent.h"

UFPSWidgetBase* UPlayerUIComponent::GetDrawedAimWidget() const
{
    return CachedDrawedAimWidget;
}

void UPlayerUIComponent::SetDrawedAimWidget(UFPSWidgetBase* InDrawedAimWidget)
{
    CachedDrawedAimWidget = InDrawedAimWidget;
}
