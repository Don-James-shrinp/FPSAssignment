// Origin OvO CopyRight Reserved


#include "Widgets/FPSScoreBoardWidget.h"
#include "Widgets/FPSPlayerScoreRowWidget.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerState/FPSPlayerState.h"

void UFPSScoreBoardWidget::RefreshPlayerList()
{
	if (!PlayerScrollBox || !PlayerRowClass) return;

	PlayerScrollBox->ClearChildren();

	AGameStateBase* GameState = GetWorld()->GetGameState();

	if (!GameState) return;
	UFPSPlayerScoreRowWidget* TableNameRow = CreateWidget<UFPSPlayerScoreRowWidget>(this, PlayerRowClass);
	TableNameRow->SetDisplayTexts(FText::FromString(FString(TEXT("Player"))), FText::FromString(FString(TEXT("Kills"))));
	PlayerScrollBox->AddChild(TableNameRow);
	TArray<APlayerState*> PlayerArray = GameState->PlayerArray;

	for (APlayerState* PlayerState : PlayerArray)
	{
		if (!PlayerState) continue;
		UFPSPlayerScoreRowWidget* Row = CreateWidget<UFPSPlayerScoreRowWidget>(this, PlayerRowClass);
		if (AFPSPlayerState* FPSPlayerState = Cast<AFPSPlayerState>(PlayerState))
		{
			Row->Setup(FPSPlayerState);

			PlayerScrollBox->AddChild(Row);
		}
	}
}
