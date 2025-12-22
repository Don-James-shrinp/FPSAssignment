// Origin OvO CopyRight Reserved


#include "AnimInstances/FPSCharacterAnimInstance.h"
#include "Characters/FPSCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFPSCharacterAnimInstance::NativeInitializeAnimation()
{
	if (OwningCharacter = Cast<AFPSCharacterBase>(TryGetPawnOwner()))
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UFPSCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();  //  获得速度(矢量)的模长，仅考虑x和y方向，即在xy平面上的移动速度

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared() > 0.f;
}
