// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//setting tracks throttle, which is equal at the same point of time
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO prevent double speed due to manual input
	return;
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//setting tracks throttle, which is equal and opposite at the same point of time
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//TODO prevent double speed due to manual input
	return;
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	return;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//getting forward vector and MoveToPlayer() normal vector
	auto ForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	//creating the required throw passed to throttle to move forward and turn right
	auto ThrowDotProduct = FVector::DotProduct(AIForwardIntention, ForwardDirection);
	auto ThrowCrossProduct = FVector::CrossProduct(ForwardDirection, AIForwardIntention).Z;
	IntendMoveForward(ThrowDotProduct);
	IntendTurnRight(ThrowCrossProduct);
}