// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSWidgetBase.generated.h"

class UPlayerUIComponent;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;  //  此Widget被创建时调用一次

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Player UI Component Initialized"))  //  BlueprintImplementableEvent表示由Blueprint实现
	void BP_OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* OwningPlayerUIComponent);  //  用于在NativeOnInitialized中进行一些初始化操作，比如说绑定Delegate的回调函数
	
};
