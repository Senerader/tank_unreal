// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Actor.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	if (ControlledTank != NULL){
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank: %s found"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("NO CONTROLLED TANK FOUND"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO make aiming at crosshair defined in UI
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	//checking if there exists controlled tank
	if (!GetControlledTank()) {
		return;
	}

	//TODO get world crosshair as ray-trace, if it hits landscape - tell the controlled tank to aim at crosshair
	return;
}