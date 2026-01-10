// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "PlayerUIComponent.generated.h"

class UFPSWidgetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoNumberChangedDelegate, int32, NewAmmoNumber, int32, MaxAmmoNumber);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);
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

	UFUNCTION(BlueprintPure, Category = "FPS|UI")
	UFPSWidgetBase* GetDrawedAimWidget() const;

	UFUNCTION(BlueprintCallable, Category = "FPS|UI")
	void SetDrawedAimWidget(UFPSWidgetBase* InDrawedAimWidget);
private:
	UFPSWidgetBase* CachedDrawedAimWidget;
};
