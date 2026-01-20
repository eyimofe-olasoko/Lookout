// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitchingWidget.h"
#include "CameraSwitcher.h"
#include "LookoutCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCameraSwitchingWidget::NativeConstruct()
{
	//Setting the buttons with the on clicked event functions
	SwitchCameraButton->OnClicked.AddDynamic(this, &UCameraSwitchingWidget::OnSwitchCameraButtonClicked);
	BackButton->OnClicked.AddDynamic(this, &UCameraSwitchingWidget::OnBackButtonClicked);
	
	//Getting the player controller
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	//Setting the input mode to UI only when the widget is in the viewport and adding mouse cursor
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
	
	//Creating a ref to actors
	CameraSwitcherActorRef =
	Cast<ACameraSwitcher>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		ACameraSwitcher::StaticClass()
		));
	
	LookoutCharacterRef = Cast<ALookoutCharacter>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		ALookoutCharacter::StaticClass()
		));
}

void UCameraSwitchingWidget::OnSwitchCameraButtonClicked()
{
	//Incrementing camera counter by one when the switch button is clicked
	CameraCounter++;
	
	if (CameraCounter == 1)
	{
		//Setting main camera to active
		CameraSwitcherActorRef->SetMainCameraActive();
		
		//Switch player camera to the current active camera in the camera switcher actor
		GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef, 0.5f);
	}
	
	if (CameraCounter == 2)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Working"));
		
		CameraSwitcherActorRef->SetSecondCameraActive();
		
		//Switch player camera to the current active camera in the camera switcher actor
		GetOwningPlayer()->SetViewTargetWithBlend(CameraSwitcherActorRef, 0.5f);
		
		//Setting the camera counter to 0 so the player switches back to the first camera
		CameraCounter = 0;
	}
}

void UCameraSwitchingWidget::OnBackButtonClicked()
{
	if (LookoutCharacterRef)
	{
		//Switching back to player camera
		GetOwningPlayer()->SetViewTargetWithBlend(LookoutCharacterRef, 0.5f);
		
		//Removing widget and setting input back to game only and disabling mouse
		LookoutCharacterRef->SetInputModeGameOnly();
	}
	
}

