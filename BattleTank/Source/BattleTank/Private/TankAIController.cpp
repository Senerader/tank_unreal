// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = GetPawn();
	TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!(PossesedTank)){ return; }

		//subscrive our local  method to Tank's death method
		PossesedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedDeath);
	}
}

void ATankAIController::OnPossesedDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AI Tank died"));
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//outputs the position of player tank

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	if (PlayerTank && TankAimingComponent)
	{
		//move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius in cm

		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		//if AI tank is locked then fire
		if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
		{
			TankAimingComponent->Fire();
		}

	}
}


