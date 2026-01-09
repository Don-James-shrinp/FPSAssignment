// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/FPSCharacterBase.h"
#include "FPSEnemyCharacter.generated.h"

class UEnemyUIComponent;
/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSEnemyCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()

public:
	AFPSEnemyCharacter();

	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;
private:
	void InitStartupData();

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UEnemyUIComponent* EnemyPawnUIComponent;
#pragma endregion

};
