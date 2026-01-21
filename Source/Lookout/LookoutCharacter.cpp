// Copyright Epic Games, Inc. All Rights Reserved.

#include "LookoutCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Lookout.h"
#include "Kismet/GameplayStatics.h"

ALookoutCharacter::ALookoutCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void ALookoutCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALookoutCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ALookoutCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALookoutCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALookoutCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ALookoutCharacter::LookInput);
		
		//Zooming in and out
		EnhancedInputComponent->BindAction(ZoomInOutAction, ETriggerEvent::Triggered, this, &ALookoutCharacter::ZoomInOutInput);
		
		//Interacting 
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ALookoutCharacter::InteractInput);
	}
	else
	{
		UE_LOG(LogLookout, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
	
	//Creating a ref to camera switcher actor
	CameraSwitcherActorRef =
	Cast<ACameraSwitcher>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		ACameraSwitcher::StaticClass()
		));
	
}

void ALookoutCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DesktopWidget = CreateWidget<UDesktopWidget>(GetWorld(), DesktopWidgetClass);
	
	//Checking if the widget is successfully initialized
	if (DesktopWidgetClass && DesktopWidget != nullptr)
	{
		DesktopWidget->AddToViewport();
	}
	
	//Setting max fov to the default fov of the first person character
	CurrentFov = FirstPersonCameraComponent->FieldOfView;
}

void ALookoutCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ALookoutCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ALookoutCharacter::ZoomInOutInput(const FInputActionValue& Value)
{
	//Getting the input value and assigning it to scroll value
	const float ScrollValue = Value.Get<float>();
	
	//If the player is not scrolling exit the function
	if (ScrollValue == 0.f) return;
	
	//Getting the scroll value (-1 for Down, +1 for Up) and s
	CurrentFov -= ScrollValue * ZoomSpeed;
	CurrentFov  = FMath::Clamp(CurrentFov , MinFov, MaxFov);
	
	//Setting the player's fov to current fov
	FirstPersonCameraComponent->SetFieldOfView(CurrentFov);
}

void ALookoutCharacter::InteractInput(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Working"));
}

void ALookoutCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ALookoutCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ALookoutCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ALookoutCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ALookoutCharacter::SetInputModeGameOnly()
{
	//Setting input mode to game only and disabling mouse cursor
	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;

		if (CameraSwitchingWidget->IsInViewport())
		{
			CameraSwitchingWidget->RemoveFromParent();
			
			//Setting all camera switcher cameras to inactive for performance
			CameraSwitcherActorRef->SetAllCamerasToInactive();
		}
	}
}

void ALookoutCharacter::AddCameraSwitchWidgetToViewport()
{
	CameraSwitchingWidget = CreateWidget<UCameraSwitchingWidget>(GetWorld(), CameraSwitchingWidgetClass);
	
	if (CameraSwitchingWidget)
	{
		CameraSwitchingWidget->AddToViewport();
		
		DesktopWidget->RemoveFromParent();
	}
}
