// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//outputs the position of player tank

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		AITank->AimAt(PlayerTank->GetActorLocation());

		AITank->Fire();
		//TODO don't fire any frame
	}
}