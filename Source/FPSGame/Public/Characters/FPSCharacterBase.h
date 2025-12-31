// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "FPSCharacterBase.generated.h"

class UFPSAbilitySystemComponent;
class UDataAsset_StartupDataBase;
class UFPSAttributeSet;
UCLASS()
class FPSGAME_API AFPSCharacterBase : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	AFPSCharacterBase();

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;  //  IAbilitySystemInterface定义的接口，用于获取ASC

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
protected:
	virtual void PossessedBy(AController* NewController) override;  //  APawn的接口，当一个APawn被Controller Possessed时调用


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UFPSAbilitySystemComponent* FPSAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UFPSAttributeSet* FPSAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartupDataBase> CharacterStartupData;

	FORCEINLINE UFPSAbilitySystemComponent* GetFPSAbilitySystemComponent() const { return FPSAbilitySystemComponent; }
};
