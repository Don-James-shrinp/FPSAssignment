// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/FPSCharacterBase.h"
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

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
 	
	TObjectPtr<UCameraComponent> FirstPersonCamera;  //  第一人称相机组件

#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Look(const FInputActionValue& InputActionValue);
#pragma endregion

	
};
