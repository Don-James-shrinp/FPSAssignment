// Origin OvO CopyRight Reserved


#include "Characters/FPSPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/FPSInputComponent.h"
#include "FPSGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAssets/StartupData/DataAsset_PlayerStartupData.h"

AFPSPlayerCharacter::AFPSPlayerCharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->bEnableFirstPersonScale = true;
	FirstPersonCamera->bEnableFirstPersonFieldOfView = true;
	FirstPersonCamera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;  //  这里与TPS的处理方式有点不同，需要让相机在Yaw的旋转影响角色的Yaw Rotation，因此要使用此设置
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

}

void AFPSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Didn't Assign Input Config Data Asset"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UFPSInputComponent* FPSInputComponent = CastChecked<UFPSInputComponent>(PlayerInputComponent);  //  检查Cast是否转化成功

	//  绑定Input事件的回调函数

	FPSInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		FPSGameplayTags::InputTag_Move, 
		ETriggerEvent::Triggered, 
		this, 
		&ThisClass::Input_Move);

	FPSInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		FPSGameplayTags::InputTag_Look,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Look);

	FPSInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		FPSGameplayTags::InputTag_Jump,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_Jump
	);

	FPSInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		FPSGameplayTags::InputTag_Jump,
		ETriggerEvent::Completed,
		this,
		&ThisClass::Input_StopJumping
	);

}

void AFPSPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartupData.IsNull())
	{
		if (UDataAsset_StartupDataBase* LoadedData = CharacterStartupData.LoadSynchronous())  //  加载Startup DataAsset
		{
			int32 AbilityApplyLevel = 1;

			LoadedData->GiveToAbilitySystemComponent(FPSAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}

void AFPSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();  //  获取输入的Axis2D

	const FRotator MovementRotation(0.f, GetController()->GetControlRotation().Yaw, 0.f);  //  获取Pawn的Controller Rotation，对于平面上的移动来说，我们只关注绕z轴的旋转即Yaw

	if (MovementVector.Y != 0.f)  //  上下有输入(W, S的输入)，需要进行前后的移动
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);  //  获得前向向量

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFPSPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2d>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AFPSPlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AFPSPlayerCharacter::Input_StopJumping(const FInputActionValue& InputActionValue)
{
	StopJumping();
}
