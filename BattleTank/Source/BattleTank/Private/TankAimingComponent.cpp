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
	PrimaryComponentTick.bCanEverTick = true; 

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (RoundsLeft <= 0)
	{
	FiringState = EFiringState::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeSec) 
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

	return;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
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
		AimDirection = LaunchSpeedVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
	}
	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }
	//receives vector coordinates
	//changes the initial position according to AimDirection
	//Converting Aimdirection to Rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	
	auto DeltaRotation = AimAsRotator - BarrelRotator;
	
	//changing barrel elevation and turret yaw frame independently through their respective classes
	Barrel->ElevateBarrel(DeltaRotation.Pitch);
	//always yaw the shortest path
	if (FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->YawTurret(DeltaRotation.Yaw);
	}
	else
	{
		Turret->YawTurret(-DeltaRotation.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	return  !(Barrel->GetForwardVector().Equals(AimDirection, 0.01));
}

void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
	return;
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBP)) { return; }
		//spawn actor at firing socket.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketTransform(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		RoundsLeft--;
	}
	return;
}

EFiringState UTankAimingComponent::GetFiringState()  const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}
