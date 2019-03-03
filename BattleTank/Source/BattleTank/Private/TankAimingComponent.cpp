// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector WorldHitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector LaunchSpeedVelocity = FVector(0.f);
	FVector ProjectileStartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//checking if it is possible to create the projectile velocity for given cursor position
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchSpeedVelocity,
		ProjectileStartLocation,
		WorldHitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = LaunchSpeedVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	//do nothing if no solution was found
	return;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* SetBarrel)
{
	Barrel = SetBarrel;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

	//receives vector coordinates
	//changes the initial position according to AimDirection
	//Converting Aimdirection to Rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	
	auto DeltaRotation = AimAsRotator - BarrelRotator;
	
	Barrel->ElevateBarrel(5);
}
