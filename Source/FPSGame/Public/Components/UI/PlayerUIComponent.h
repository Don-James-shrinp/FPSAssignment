// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoNumberChangedDelegate, int32, NewAmmoNumber);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon, FString, TextContent);
/**
 * 
 */
UCLASS()
class FPSGAME_API UPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAmmoNumberChangedDelegate OnAmmoNumberChanged;  //  子弹数量发生变化时进行BroadCast

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;
};
