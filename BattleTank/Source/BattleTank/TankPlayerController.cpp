// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "Public/Tank.h"
#include "Engine/Classes/Camera/PlayerCameraManager.h"
#include "Engine/World.h"

#define OUT
void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	if (!GetPawn()) { return; } //e.g not possesing
	ControlledTank = GetPawn();
	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(TankAimingComponent))
	{
		FoundAimingComponent(TankAimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Aiming Component found for %s"), *ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	if (!GetPawn()) { return; }
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	ControlledTank = GetPawn();
	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }

	FVector AimHitLocation;
	if (GetSightRayHitLocation(AimHitLocation)) {
		TankAimingComponent->AimAt(AimHitLocation);
	}
	return;
}

//checks if the player UI viewpoint has hit the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& AimHitLocation)
{
	//find crosshair position in pix coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairLocationX, ViewPortSizeY * CrosshairLocationY);

	
	//deproject it on screen
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//ray-trace through look direction
		//checking if our camera hits something
		return GetLookVectorHitLocation(LookDirection, AimHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& DeprojectDirection) const
{
	FVector DeprojectLocation; //To be discarded
	return (DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		DeprojectLocation,
		DeprojectDirection)
		);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& AimHitLocation) const
{
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	FHitResult LineTraceHit;
	if (GetWorld()->LineTraceSingleByChannel(LineTraceHit,StartLocation,EndLocation,ECollisionChannel::ECC_Camera)) 
	{
		AimHitLocation = LineTraceHit.Location;
		return true;
	}
	//unsuccessful hit
	AimHitLocation = FVector(0);
	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		//subscrive our local  method to Tank's death method
		PossesedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedDeath);
	}
}

void ATankPlayerController::OnPossesedDeath()
{
	if (!GetPawn()) { return; }
	StartSpectatingOnly();
}
