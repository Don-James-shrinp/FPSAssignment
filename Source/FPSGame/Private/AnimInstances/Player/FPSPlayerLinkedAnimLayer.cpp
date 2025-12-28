// Origin OvO CopyRight Reserved


#include "AnimInstances/Player/FPSPlayerLinkedAnimLayer.h"
#include "AnimInstances/Player/FPSPlayerAnimInstance.h"

UFPSPlayerAnimInstance* UFPSPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UFPSPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}