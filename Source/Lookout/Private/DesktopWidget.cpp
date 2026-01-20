// Fill out your copyright notice in the Description page of Project Settings.


#include "DesktopWidget.h"

void UDesktopWidget::NativeConstruct()
{
	//Setting the buttons with the on clicked event functions
	CameraAppButton->OnClicked.AddDynamic(this, &UDesktopWidget::OnCameraAppButtonClicked);
}

void UDesktopWidget::OnCameraAppButtonClicked()
{
	
}
