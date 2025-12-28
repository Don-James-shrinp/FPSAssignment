// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/FPSCharacterBase.h"
#include "GameplayTagContainer.h"
#include "FPSPlayerCharacter.generated.h"

class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()

public:
	AFPSPlayerCharacter();

protected:
	/** Allows a Pawn to set up custom input bindings. Called upon possession by a PlayerController, using the InputComponent created by CreatePlayerInputComponent(). */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;  //  APawn提供的接口，用于进行自定义的输入绑定
	virtual void PossessedBy(AController* NewController) override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
 	
	UCameraComponent* FirstPersonCamera;  //  第一人称相机组件

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

	
};
