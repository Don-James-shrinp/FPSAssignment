// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/FPSWidgetBase.h"
#include "Components/TextBlock.h"
#include "FPSPlayerScoreRowWidget.generated.h"

class AFPSPlayerState;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSPlayerScoreRowWidget : public UFPSWidgetBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score|UI")
	void Setup(AFPSPlayerState* InPlayerState);  //  通过传入的PlayerState设置当前行的信息

	UFUNCTION(BlueprintCallable, Category = "Score|UI")
	void SetDisplayTexts(FText NameText, FText CountText);

protected:
	UPROPERTY(meta = (BindWidget))  //  使用BindWidget将其与UMG中的同名空间绑定
	UTextBlock* PlayerNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillCountText;
};
