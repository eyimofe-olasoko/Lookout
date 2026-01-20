// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CameraSwitcher.h"
#include "CameraSwitchingWidget.generated.h"

/**
 * 
 */

class ALookoutCharacter;

UCLASS()
class LOOKOUT_API UCameraSwitchingWidget : public UUserWidget
{
	GENERATED_BODY()
	

private:
	
	APlayerController* PlayerController;
	
	//Getting a ref to the camera switcher actor
	ACameraSwitcher* CameraSwitcherActorRef;
	
	//Getting ref to player character
	ALookoutCharacter* LookoutCharacter;
	
	//Variable to keep track of camera switching order
	int CameraCounter = 0;

	
public:
	
	//Creating the buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SwitchCameraButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;
	
	virtual void NativeConstruct() override;
	
	//Creating on clicked event functions for the buttons
	UFUNCTION(BlueprintCallable)
	void OnSwitchCameraButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();
	
	
};
