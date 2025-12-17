// Origin OvO CopyRight Reserved


#include "Characters/FPSCharacterBase.h"

// Sets default values
AFPSCharacterBase::AFPSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

}
