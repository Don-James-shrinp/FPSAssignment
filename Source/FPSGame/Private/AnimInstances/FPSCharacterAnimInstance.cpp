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

	Velocity = OwningCharacter->GetVelocity();
	GroundSpeed = Velocity.Size2D();  //  获得速度(矢量)的模长，仅考虑x和y方向，即在xy平面上的移动速度

	bShouldMove = OwningMovementComponent->GetCurrentAcceleration().SizeSquared() > 0.f
				&& GroundSpeed > 0.01f;

	const FRotator CharacterRotation = OwningCharacter->GetActorRotation();

	float CaculatedDirection = CalculateDirection(Velocity, CharacterRotation);

	if (OwningMovementComponent->bOrientRotationToMovement)
	{
		Direction = FMath::Clamp(CaculatedDirection, -45.f, 45.f);
	}
	else
	{
		Direction = CaculatedDirection;
	}
}
