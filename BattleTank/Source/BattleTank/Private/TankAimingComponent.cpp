// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
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


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector WorldHitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector LaunchSpeedVelocity = FVector(0.f);
	FVector ProjectileStartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//obtaining suggested projectile velocity and deawing debug line.
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchSpeedVelocity,
		ProjectileStartLocation,
		WorldHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
	)
	{
		auto TankName = GetOwner()->GetName();
		auto AimDirection = LaunchSpeedVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s firing at %s"),
			*TankName,
			*AimDirection.ToString()
		);
	}
	return;
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* SetBarrel)
{
	Barrel = SetBarrel;
	BarrelLocation = Barrel->GetComponentLocation();
}
