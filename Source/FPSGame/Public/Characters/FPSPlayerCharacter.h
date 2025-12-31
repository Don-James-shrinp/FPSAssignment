// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/FPSCharacterBase.h"
#include "GameplayTagContainer.h"
#include "FPSPlayerCharacter.generated.h"

class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UPlayerCombatComponent;
class UPlayerUIComponent;
class UPawnUIComponent;
/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()

public:
	AFPSPlayerCharacter();
	
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;

protected:
	/** Allows a Pawn to set up custom input bindings. Called upon possession by a PlayerController, using the InputComponent created by CreatePlayerInputComponent(). */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;  //  APawn提供的接口，用于进行自定义的输入绑定
	virtual void PossessedBy(AController* NewController) override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;  //  第一人称相机组件

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* PlayerCombatComponet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UPlayerUIComponent* PlayerUIComponent;

#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_Jump(const FInputActionValue& InputActionValue);

	void Input_StopJumping(const FInputActionValue& InputActionValue);

	void Ability_Input_Pressed(FGameplayTag InInputTag);

	void Ability_Input_Released(FGameplayTag InInputTag);
#pragma endregion

public:
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponet; }
	
};
