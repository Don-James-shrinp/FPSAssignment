// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/FPSWidgetBase.h"
#include "Components/ScrollBox.h"
#include "FPSScoreBoardWidget.generated.h"


class UFPSPlayerScoreRowWidget;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSScoreBoardWidget : public UFPSWidgetBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score|UI")
	void RefreshPlayerList();

protected:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* PlayerScrollBox;

	UPROPERTY(EditDefaultsOnly, Category = "Score|UI")
	TSubclassOf<UFPSPlayerScoreRowWidget> PlayerRowClass;
};
