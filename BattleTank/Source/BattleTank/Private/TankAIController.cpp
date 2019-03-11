// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = GetPawn();
	TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//outputs the position of player tank

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(PlayerTank && TankAimingComponent))
	{
		//move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius in cm

		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
		TankAimingComponent->Fire();

	}
}