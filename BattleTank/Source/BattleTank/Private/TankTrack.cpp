// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	//calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//calculate required acceleration to fix slippping speed back to 0
	auto DeltaTime = GetWorld()->GetDeltaSeconds(); //Getting the time span of a single frame
	auto CorrectionAcceleration = -SlippageSpeed * GetRightVector() / DeltaTime;
	//calculate and apply sideways force
	auto TankBody = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankBody->GetMass() * CorrectionAcceleration / 2; //two tracks
	TankBody->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive the tank if OnHit
	DriveTrack();
	//Apply sideways force if OnHit
	ApplySidewaysForce();
	//Resetting current throttle to remove infinite motion
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//calculating applied force vector with throttle clamped value
	auto ForceApplied = GetForwardVector() * FMath::Clamp<float>(CurrentThrottle, -1, 1) * TrackMaxDrivingForce;
	//getting the point of force application (track center point)
	auto ForceLocation = GetComponentLocation();
	//getting the root component
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//applying the force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}