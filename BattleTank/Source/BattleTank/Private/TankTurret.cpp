// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Classes/Engine/World.h"

void UTankTurret::YawTurret(float RelativeSpeed)
{
	//changing yaw turret angle.
	//make it frame independent.
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto YawChange = RelativeSpeed * MaxDegreesPerSecond *(GetWorld()->DeltaTimeSeconds);
	auto RawNewYaw = RelativeRotation.Yaw + YawChange;

	//no need to clamp yaw since it can rotate 360.
	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
}