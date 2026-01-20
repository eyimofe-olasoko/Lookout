// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "CameraSwitchingWidget.h"
#include "DesktopWidget.generated.h"

/**
 * 
 */
class ALookoutCharacter;

UCLASS()
class LOOKOUT_API UDesktopWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	
	APlayerController* PlayerController;
	
	ALookoutCharacter* LookoutCharacterRef;
	
public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CameraAppButton;

	UFUNCTION(BlueprintCallable)
	void OnCameraAppButtonClicked();
	
	//Adding ref to the camera switching widget
	UPROPERTY(editAnywhere, Category = "Widgets")
	TSubclassOf<class UCameraSwitchingWidget> CameraSwitchingWidgetClass;
	
	UPROPERTY()
	class UCameraSwitchingWidget* CameraSwitchingWidget;
	
	virtual void NativeConstruct() override;
	
	
};
