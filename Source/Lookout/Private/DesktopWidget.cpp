// Fill out your copyright notice in the Description page of Project Settings.

#include "DesktopWidget.h"
#include "LookoutCharacter.h"
#include "Kismet/GameplayStatics.h"

void UDesktopWidget::NativeConstruct()
{
	//Setting the buttons with the on clicked event functions
	CameraAppButton->OnClicked.AddDynamic(this, &UDesktopWidget::OnCameraAppButtonClicked);
	
	//Getting the player controller
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	
	//Getting character actor ref
	LookoutCharacterRef = Cast<ALookoutCharacter>(UGameplayStatics::GetActorOfClass(
		GetWorld(),
		ALookoutCharacter::StaticClass()
		));
}

void UDesktopWidget::OnCameraAppButtonClicked()
{
	/*WIDGET SWITCHER ONLY WORKS FOR SAME HUD MOT DIFFERENT WIDGET BLUEPRINTS*/
	
	//Displaying the camera switching widget from the lookout character actor
	if (LookoutCharacterRef)
	{
		LookoutCharacterRef->AddCameraSwitchWidgetToViewport();
	}

}