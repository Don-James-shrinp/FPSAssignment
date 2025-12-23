// Origin OvO CopyRight Reserved


#include "AnimInstances/Player/FPSPlayerAnimInstance.h"
#include "Characters/FPSPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFPSPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningPlayerCharacter = Cast<AFPSPlayerCharacter>(OwningCharacter);
	}
}

void UFPSPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningMovementComponent) return;
	bIsFalling = OwningMovementComponent->IsFalling();
}


