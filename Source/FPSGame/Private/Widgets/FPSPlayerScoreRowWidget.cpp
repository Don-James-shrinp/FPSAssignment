// Origin OvO CopyRight Reserved


#include "Widgets/FPSPlayerScoreRowWidget.h"
#include "PlayerState/FPSPlayerState.h"

void UFPSPlayerScoreRowWidget::Setup(AFPSPlayerState* InPlayerState)
{
	if (!InPlayerState) return;


	SetDisplayTexts(
		FText::FromString(InPlayerState->GetPawn()->GetActorNameOrLabel()),
		FText::AsNumber(InPlayerState->KillCount)
	);

}

void UFPSPlayerScoreRowWidget::SetDisplayTexts(FText NameText, FText CountText)
{
	PlayerNameText->SetText(NameText);
	KillCountText->SetText(CountText);
}
