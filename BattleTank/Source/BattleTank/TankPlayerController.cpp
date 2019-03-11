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

	ControlledTank = GetControlledTank();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Aiming Component found for %s"), *ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }

	FVector AimHitLocation;
	if (GetSightRayHitLocation(AimHitLocation)) {
		GetControlledTank()->AimAt(AimHitLocation);
	}
	//TODO get world crosshair as ray-trace, if it hits landscape - tell the controlled tank to aim at crosshair
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
	if (GetWorld()->LineTraceSingleByChannel(LineTraceHit,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility)) 
	{
		AimHitLocation = LineTraceHit.Location;
		return true;
	}
	//unsuccessful hit
	AimHitLocation = FVector(0);
	return false;
}
