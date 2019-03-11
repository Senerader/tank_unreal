// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector AimHitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(AimHitLocation, LaunchSpeed);
	return;
}

void ATank::Fire() 
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTimeSec;
	if (LocaLBarrel && isReloaded)
	{
		//spawn actor at firing socket.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			LocaLBarrel->GetSocketTransform(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	return;
}
