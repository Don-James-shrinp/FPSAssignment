// Origin OvO CopyRight Reserved


#include "GameState/FPSGameState.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/FPSScoreBoardWidget.h"

void AFPSGameState::OnRep_CurrentGameState(ECompetitionGameState OldGameState)
{
	if (CurrentGameState == ECompetitionGameState::AllWaveDone)
	{
        ShowScoreBoardUI();
	}
}

void AFPSGameState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AFPSGameState, CurrentGameState);
}

void AFPSGameState::ShowScoreBoardUI()
{
	if (GetNetMode() == NM_DedicatedServer || !ScoreBoardWidgetClass) return;
    APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
    if (!PC) return;

    UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(PC, ScoreBoardWidgetClass);

    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();

        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(WidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = true;
    }

}
