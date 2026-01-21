// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitcher.h"

// Sets default values
ACameraSwitcher::ACameraSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initializing the camera components
	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	//Setting main camera to be the root component
	RootComponent = MainCamera;
	
	SecondCamera = CreateDefaultSubobject<UCameraComponent>("SecondCamera");
	SecondCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACameraSwitcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraSwitcher::SetMainCameraActive()
{
	//Setting the main camera to active and second to inactive when the player switches
	MainCamera->SetActive(true);
	SecondCamera->SetActive(false);
}

void ACameraSwitcher::SetSecondCameraActive()
{
	SecondCamera->SetActive(true);
	MainCamera->SetActive(false);
}

void ACameraSwitcher::SetAllCamerasToInactive()
{
	//Setting both cameras to inactive by default for optimization
	MainCamera->SetActive(false);
	SecondCamera->SetActive(false);
}

