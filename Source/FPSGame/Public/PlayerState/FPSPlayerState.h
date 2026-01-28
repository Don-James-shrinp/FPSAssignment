// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	UPROPERTY(ReplicatedUsing = OnRep_KillCount, BlueprintReadOnly)
	int32 KillCount = 0;

	UFUNCTION()
	void OnRep_KillCount(int32 OldKillCount);

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
};
