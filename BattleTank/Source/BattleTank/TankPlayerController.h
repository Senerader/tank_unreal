// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATank *GetControlledTank() const;

	//starts at initialziation
	virtual void BeginPlay() override;

	//ticks every frame
	virtual void Tick(float DeltaTime) override;

	//moving the barrel so shot would hit where crosshair intersects the world
	void AimAtCrosshair();
protected:
	bool GetSightRayHitLocation(FVector& AimHitLocation);

	bool GetLookDirection(FVector2D ScreenLocation, FVector& DeprojectDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& AimHitLocation) const;

private:
	ATank *ControlledTank = NULL;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
