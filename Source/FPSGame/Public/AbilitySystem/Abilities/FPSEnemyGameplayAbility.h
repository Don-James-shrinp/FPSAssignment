// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/FPSGameplayAbility.h"
#include "FPSEnemyGameplayAbility.generated.h"

class AFPSEnemyCharacter;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSEnemyGameplayAbility : public UFPSGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "FPS|Ability")
	AFPSEnemyCharacter* GetEnemyCharacterFromActorInfo();

private:
	TWeakObjectPtr<AFPSEnemyCharacter> CachedEnemyCharacter;
};
