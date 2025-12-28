// Origin OvO CopyRight Reserved


#include "Characters/FPSCharacterBase.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "AbilitySystem/FPSAttributeSet.h"

// Sets default values
AFPSCharacterBase::AFPSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	FPSAbilitySystemComponent = CreateDefaultSubobject<UFPSAbilitySystemComponent>(TEXT("FPSAbilitySystemComponent"));

	FPSAttributeSet = CreateDefaultSubobject<UFPSAttributeSet>(TEXT("FPSAttributeSet"));

}

UAbilitySystemComponent* AFPSCharacterBase::GetAbilitySystemComponent() const
{
	return GetAbilitySystemComponent();
}

UPawnCombatComponent* AFPSCharacterBase::GetPawnCombatComponent() const
{
	return nullptr;
}

void AFPSCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (FPSAbilitySystemComponent)
	{
		FPSAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartupData.IsNull(), TEXT("Forgot to assign startup data to %s"), *GetActorNameOrLabel());  //  »∑±£∏≥”Ë¡ÀStartupData
	}
}
