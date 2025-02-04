// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * Helps player to aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//starts at initialziation
	virtual void BeginPlay() override;

	//ticks every frame
	virtual void Tick(float DeltaTime) override;

	//moving the barrel so shot would hit where crosshair intersects the world
	void AimAtCrosshair();
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	bool GetSightRayHitLocation(FVector& AimHitLocation);

	bool GetLookDirection(FVector2D ScreenLocation, FVector& DeprojectDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& AimHitLocation) const;

	UFUNCTION()
	void OnPossesedDeath();

private:
	APawn *ControlledTank = NULL;

	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	virtual void SetPawn(APawn * InPawn) override;
};
