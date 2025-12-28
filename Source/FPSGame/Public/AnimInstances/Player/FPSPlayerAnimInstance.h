// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/FPSCharacterAnimInstance.h"
#include "FPSPlayerAnimInstance.generated.h"

class AFPSPlayerCharacter;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSPlayerAnimInstance : public UFPSCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	AFPSPlayerCharacter* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	bool bIsFalling;
	
};
