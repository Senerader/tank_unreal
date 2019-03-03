// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //forward declaration

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector WorldHitLocation, float LaunchSpeed);

	//TODO set turret reference
	void SetBarrelReference(UTankBarrel* SetBarrel);

private:
	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel *Barrel = nullptr;
};
