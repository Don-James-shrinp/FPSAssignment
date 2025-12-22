// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/FPSAnimInstanceBase.h"
#include "FPSCharacterAnimInstance.generated.h"

class AFPSCharacterBase;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSCharacterAnimInstance : public UFPSAnimInstanceBase
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<AFPSCharacterBase> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	float GroundSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	bool bHasAcceleration;  //  是否有加速度
};
