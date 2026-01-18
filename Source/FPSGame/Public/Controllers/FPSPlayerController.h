// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	virtual FGenericTeamId GetGenericTeamId() const override;
};
