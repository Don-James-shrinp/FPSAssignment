// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/FPSPawnExtensionComponent.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);
/**
 * 
 */
UCLASS()
class FPSGAME_API UPawnUIComponent : public UFPSPawnExtensionComponent  //  定义公有的Delegate
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)  //  BlueprintAssignable表示可以由Blueprint来实现回调
	FOnPercentChangedDelegate OnCurrentHealthChanged;
	
};
