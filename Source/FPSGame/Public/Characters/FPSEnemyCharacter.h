// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/FPSCharacterBase.h"
#include "FPSEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSEnemyCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()
protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;
private:
	void InitStartupData();
};
