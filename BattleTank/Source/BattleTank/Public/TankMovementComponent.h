// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * responsible for driving tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Moving Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Moving Input")
	void IntendTurnRight(float Throw);

	//initializes and sets tank track components
	UFUNCTION(BlueprintCallable, Category = "Moving Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	UTankTrack *LeftTrack = nullptr;

	UTankTrack *RightTrack = nullptr;

	//overriding method to get AI mobing belocity unit vector
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
