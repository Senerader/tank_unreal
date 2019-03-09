// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{

	//calculating applied force vector with throttle clamped value
	auto ForceApplied = GetForwardVector() * FMath::Clamp<float>(Throttle, -1, 1) * TrackMaxDrivingForce;
	//getting the point of force application (track center point)
	auto ForceLocation = GetComponentLocation();
	//getting the root component
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//applying the force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}