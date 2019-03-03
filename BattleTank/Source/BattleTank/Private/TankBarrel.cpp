// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Core/Public/Math/UnrealMathUtility.h"
#include "Classes/Engine/World.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	//changing elevation angle.
	//make it frame independent.
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds);
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationAngle, MaxElevationAngle);
	SetRelativeRotation(FRotator(ClampedElevation, 0 , 0));

}