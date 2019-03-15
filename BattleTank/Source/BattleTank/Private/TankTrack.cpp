// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//calculate required acceleration to fix slippping speed back to 0
	auto CorrectionAcceleration = -SlippageSpeed * GetRightVector() / DeltaTime;
	//calculate and apply sideways force
	auto TankBody = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankBody->GetMass() * CorrectionAcceleration/2; //two tracks
	TankBody->AddForce(CorrectionForce);
	
	return;
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm hit"));
}

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