// Origin OvO CopyRight Reserved


#include "Widgets/FPSWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PlayerUIComponent.h"

void UFPSWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))  //  只要Pawn实现了该IPawnUIInterface接口就能够被成功Cast
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}
