// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UPawnUIComponent;
class UPlayerUIComponent;
class UEnemyUIComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSGAME_API IPawnUIInterface
{
	GENERATED_BODY()
public:
	virtual UPawnUIComponent* GetPawnUIComponent() const;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const;
public:
};
