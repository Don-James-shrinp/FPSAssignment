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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	float GroundSpeed;  //  移动速度（用于移动的2D Blend Space）

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	bool bShouldMove;  //  是否有加速度（用于在Idel和Move之间进行状态转移的判定）

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	float Direction;  //  移动方向（用于移动的2D Blend Space）

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	FVector Velocity;
};
