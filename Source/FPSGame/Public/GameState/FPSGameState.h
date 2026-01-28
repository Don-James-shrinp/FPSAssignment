// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSTypes/FPSEnumTypes.h"
#include "FPSGameState.generated.h"


class UFPSScoreBoardWidget;
/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentGameState)
	ECompetitionGameState CurrentGameState;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode|UI")
	TSubclassOf<UFPSScoreBoardWidget> ScoreBoardWidgetClass;

	UFUNCTION()
	void OnRep_CurrentGameState(ECompetitionGameState OldGameState);
	
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

private:
	void ShowScoreBoardUI();
};
