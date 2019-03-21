// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//sets throttle between 1 and -1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	//max force per track
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; //m*g

private:
	UTankTrack();

	TArray<class ASprungWheel*> GetWheels() const;

	virtual void BeginPlay() override;

	void DriveTrack(float CurrentThrottle);
};
