// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = GetAITank();
	if (AITank != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("AI tank: %s found"), *(AITank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("NO AI TANK FOUND"));
	}

	PlayerTank = GetPlayerTank();
	if (PlayerTank != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("AIController: %s player tank found"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController: NO PLAYER TANK FOUND"));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//outputs the position of player tank
	AimAtPlayer();
}

ATank* ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerTankController = NULL;
	ATank* PlayerTank = NULL;
	if (GetWorld() != NULL) {
		PlayerTankController = GetWorld()->GetFirstPlayerController();
		if (PlayerTankController != NULL) {
			PlayerTank = Cast<ATank>(PlayerTankController->GetPawn());
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("NO PLAYER CONTROLLER FOUND"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("NO WORLD FOUND"));
	}
	return PlayerTank;
}

void ATankAIController::AimAtPlayer()
{
	if (GetPlayerTank() == NULL) { return; }

	//finding player world coordinates
	PlayerCoordinates = PlayerTank->GetActorLocation();
	//calling parent method for printing coordinates
	AITank->AimAt(PlayerCoordinates);
	return;
}