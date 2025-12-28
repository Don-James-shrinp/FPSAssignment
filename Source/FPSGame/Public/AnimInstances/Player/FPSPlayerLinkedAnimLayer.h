// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/FPSAnimInstanceBase.h"
#include "FPSPlayerLinkedAnimLayer.generated.h"

class UFPSPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSPlayerLinkedAnimLayer : public UFPSAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UFPSPlayerAnimInstance* GetPlayerAnimInstance() const;
};
