// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward speed and +1 max upward speed.
	void ElevateBarrel(float RelativeSpeed);

private:
	//setting up default sensible values
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationAngle = 40.f; //required to be set in blueprint!

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationAngle = 0.f; //required to be set in blueprint!

};
