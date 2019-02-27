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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}