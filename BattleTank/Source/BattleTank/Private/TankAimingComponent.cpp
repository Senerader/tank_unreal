// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should it tick?

}


void UTankAimingComponent::AimAt(FVector WorldHitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }
	FVector LaunchSpeedVelocity = FVector(0.f);
	FVector ProjectileStartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//checking if it is possible to create the projectile velocity for given cursor position
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchSpeedVelocity,
		ProjectileStartLocation,
		WorldHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = LaunchSpeedVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
	}
	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	//receives vector coordinates
	//changes the initial position according to AimDirection
	//Converting Aimdirection to Rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	
	auto DeltaRotation = AimAsRotator - BarrelRotator;
	
	//changing barrel elevation and turret yaw frame independently through their respective classes
	Barrel->ElevateBarrel(DeltaRotation.Pitch);
	Turret->YawTurret(DeltaRotation.Yaw);
}

void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
	return;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) { return; }

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTimeSec;
	if (isReloaded)
	{
		//spawn actor at firing socket.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketTransform(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	return;
}