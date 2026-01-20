// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "CameraSwitcher.generated.h"

UCLASS()
class LOOKOUT_API ACameraSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraSwitcher();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraSwitching")
	UCameraComponent* MainCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraSwitching")
	UCameraComponent* SecondCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
