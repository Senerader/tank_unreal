// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ReturnArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }
		
		AActor *SpawnedChild = SpawnPointChild->GetSpawnedActor();
		if (!SpawnedChild) { continue; }

		ASprungWheel* SpawnedSpring = Cast<ASprungWheel>(SpawnedChild);
		if (!SpawnedSpring) { continue; }

		ReturnArray.Add(SpawnedSpring);
	}
	return ReturnArray;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//calculating applied force vector with throttle clamped value
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	//Getting the wheels we would like to apply the force
	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}