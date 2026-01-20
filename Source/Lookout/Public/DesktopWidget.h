// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WidgetSwitcherSlot.h"
#include "DesktopWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOOKOUT_API UDesktopWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), EditAnywhere)
	UButton* CameraAppButton;
	
	//Creating a widget switcher variable to switch between widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), EditAnywhere)
	UWidgetSwitcher* WidgetSwitcher;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), EditAnywhere)
	UWidgetSwitcherSlot* CameraSwitcherSlot;

	UFUNCTION(BlueprintCallable)
	void OnCameraAppButtonClicked();
	
	virtual void NativeConstruct() override;
	
	
};
