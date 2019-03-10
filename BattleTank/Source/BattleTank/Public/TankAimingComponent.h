// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//enum corresponding to aiming and firing status
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

//forward declaration
class UTankBarrel; 
class UTankTurret;

//Holds parameter for barrel's and turret's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector WorldHitLocation, float LaunchSpeed);

	void SetTurretReference(UTankTurret* SetTurret);

	void SetBarrelReference(UTankBarrel* SetBarrel);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	EFiringState FiringState = EFiringState::Reloading;

private:
	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
};
